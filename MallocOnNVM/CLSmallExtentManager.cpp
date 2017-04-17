#include "CLSmallExtentManager.h"
#include "CLExtent.h"
#include "CLNVMMemoryMapManager.h"
#include <cassert>

NS_BEGIN

CLSmallExtentManager::CLSmallExtentManager():
m_pCurrentExtent(nullptr),
m_pLastExtent(nullptr)
{
}

CLSmallExtentManager::~CLSmallExtentManager()
{
}

CLExtent * CLSmallExtentManager::GetAvailableExtent(size_t expectedSize)
{
	assert(expectedSize <= SMALL_MAX_SIZE);
	expectedSize = AlignSize(expectedSize);
	if (m_pCurrentExtent == nullptr || m_pCurrentExtent->GetSize() < expectedSize)
	{
		SetCurrentExtent(expectedSize);
	}
	if (m_pCurrentExtent == nullptr)
	{
		return nullptr;
	}

	size_t currentExtentSize = m_pCurrentExtent->GetSize();
	CLExtent * pReturnExtent = nullptr;
	assert(currentExtentSize >= expectedSize);
	if (currentExtentSize != expectedSize)
	{
		pReturnExtent = SplitExtent(m_pCurrentExtent, expectedSize);
		if (pReturnExtent == nullptr)
		{
			pReturnExtent = m_pCurrentExtent;
			m_pCurrentExtent = nullptr;
		}
	}
	else
	{
		pReturnExtent = m_pCurrentExtent;
		m_pCurrentExtent = nullptr;
	}
	return pReturnExtent;
}

void CLSmallExtentManager::FreeExtent(CLExtent * pExtent)
{
	assert(pExtent);

	CLExtent * pPrevious = pExtent->GetAdjacentPreviousExtent();
	CLExtent * pNext = pExtent->GetAdjacentNextExtent();
	bool Appended = false;
	if (MergePreCheck(pPrevious, pExtent))
	{
		if (pPrevious != m_pCurrentExtent)
		{
			RemoveExtentFromExtentListArray(pPrevious);
		}
		else
		{
			m_pCurrentExtent = pExtent;
			Appended = true;
		}
		pExtent->Merge(pPrevious);
		delete pPrevious;
		if (m_pLastExtent == pPrevious)
		{
			m_pLastExtent = pExtent;
		}
	}
	if (MergePreCheck(pExtent, pNext))
	{
		if (pNext != m_pCurrentExtent)
		{
			RemoveExtentFromExtentListArray(pNext);
		}
		else
		{
			m_pCurrentExtent = pExtent;
			Appended = true;
		}
		pExtent->Merge(pNext);
		delete pNext;
		if (m_pLastExtent == pNext)
		{
			m_pLastExtent = pExtent;
		}
	}
	if (!Appended)
	{
		assert(pExtent != m_pCurrentExtent);
		AppendExtentToExtentListArray(pExtent);
		if (pExtent->GetSize() == SMALL_MAX_SIZE)
		{
			pExtent->RemoveFromAdjacentList();
			if (m_pLastExtent == pExtent)
			{
				m_pLastExtent = pExtent->GetAdjacentPreviousExtent();
			}
			TryPurge();
		}
	}
}

void CLSmallExtentManager::RecieveExtentRecovery(CLExtent * pExtent)
{
	assert(pExtent);
	pExtent->AppendToAdjacentList(m_pLastExtent);
	if (!pExtent->IsOccupied())
	{
		AppendExtent(pExtent);
	}
	m_pLastExtent = pExtent;
}

void CLSmallExtentManager::SetCurrentExtent(size_t expectedSize)
{
	if (m_pCurrentExtent != nullptr)
	{
		AppendExtent(m_pCurrentExtent);
		m_pCurrentExtent = nullptr;
	}

	unsigned int index = Size2Index(expectedSize);
	for (int i = index; i < SMALL_OBJECT_ARRAY_SIZE; ++i)
	{
		if ((m_pCurrentExtent = m_ExtentListArray[i].GetExtent()) != nullptr)
		{
			break;
		}
	}

	if (m_pCurrentExtent == nullptr)
	{
		m_pCurrentExtent = MapANewExtent();
	}
	if (m_pCurrentExtent->GetSize() == SMALL_MAX_SIZE)
	{
		m_pCurrentExtent->AppendToAdjacentList(m_pLastExtent);
		m_pLastExtent = m_pCurrentExtent;
	}
}

void CLSmallExtentManager::AppendExtent(CLExtent * pExtent)
{
	assert(pExtent);
	unsigned int index = Size2Index(pExtent->GetSize());
	assert(index < SMALL_OBJECT_ARRAY_SIZE);
	m_ExtentListArray[index].PutExtent(pExtent);
}

CLExtent * CLSmallExtentManager::MapANewExtent()
{
	void * pAddress = CLNVMMemoryMapManager::GetInstance()->MapMemory(SMALL_MAX_SIZE);
	if (pAddress == nullptr)
	{
		return nullptr;
	}
	CLExtent * pExtent = new CLExtent();
	pExtent->SetAddress(pAddress, SMALL_MAX_SIZE);
	return pExtent;
}

CLExtent * CLSmallExtentManager::SplitExtent(CLExtent * pTargetExtent,size_t expectedSize)
{
	assert(pTargetExtent);
	CLExtent * pExtent = new CLExtent();
	if (pTargetExtent->Split(pExtent, expectedSize) == nullptr)
	{
		delete pExtent;
		return nullptr;
	}
	if (pTargetExtent == m_pLastExtent)
	{
		m_pLastExtent = pExtent;
	}
	return pExtent;
}

bool CLSmallExtentManager::MergePreCheck(CLExtent * pPreviousExtent, CLExtent * pNextExtent)
{
	if (((unsigned long)(pPreviousExtent->GetNVMEndAddress()) & (PAGE_SIZE_MASK)) == 0 || ((unsigned long)(pNextExtent->GetNVMAddress())&(PAGE_SIZE_MASK) == 0))
	{
		return false;
	}
	if (!pPreviousExtent->CanMerge(pNextExtent))
	{
		return false;
	}
	return true;
}

void CLSmallExtentManager::RemoveExtentFromExtentListArray(CLExtent * pExtent)
{
	m_ExtentListArray[Size2Index(pExtent->GetSize())].RemoveExtent(pExtent);
}

void CLSmallExtentManager::AppendExtentToExtentListArray(CLExtent * pExtent)
{
	m_ExtentListArray[Size2Index(pExtent->GetSize())].PutExtent(pExtent);
}

void CLSmallExtentManager::TryPurge()
{
	if (m_ExtentListArray[SMALL_OBJECT_ARRAY_SIZE -1].GetExtentCount() >= SMALL_OBJECT_MAX_CACHE_EXTENT_COUNT)
	{
		unsigned int unmapCount = SMALL_OBJECT_MAX_CACHE_EXTENT_COUNT - (SMALL_OBJECT_MAX_CACHE_EXTENT_COUNT >> SMALL_OBJECT_CACHE_EXTENT_COUNT_PURGE_BIT);
		CLNVMMemoryMapManager::GetInstance()->UnmapMemoryAndFreeExtent(&m_ExtentListArray[SMALL_OBJECT_ARRAY_SIZE - 1], unmapCount);
	}
}

unsigned int CLSmallExtentManager::Size2Index(size_t size)
{
	assert(size >= 0 && size <= SMALL_MAX_SIZE);
	if (size <= 0)
	{
		size = SMALL_OBJECT_ALIGN;
	}
	return ((size + (1 << SMALL_OBJECT_ALIGN_BIT) - 1) >> SMALL_OBJECT_ALIGN_BIT) - 1;
}

size_t CLSmallExtentManager::Index2Size(unsigned int index)
{
	assert(index >= 0 && index <= SMALL_OBJECT_ARRAY_SIZE);
	return (index + 1) << SMALL_OBJECT_ALIGN_BIT;
}

size_t CLSmallExtentManager::AlignSize(size_t size)
{
	if (size == 0)
	{
		return 0;
	}
	size_t alginedSize = size >> SMALL_OBJECT_ALIGN_BIT << SMALL_OBJECT_ALIGN_BIT;
	if (alginedSize == size)
	{
		return size;
	}
	else
	{
		return alginedSize + SMALL_OBJECT_ALIGN;
	}
}

NS_END