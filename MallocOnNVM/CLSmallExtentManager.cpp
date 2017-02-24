#include "CLSmallExtentManager.h"
#include "CLExtent.h"
#include "CLMetaDataManager.h"
#include "CLNVMMemoryMapManager.h"
#include <cassert>

CLSmallExtentManager::CLSmallExtentManager():
m_pCurrentExtent(nullptr),
m_pLastExtent(nullptr)
{
}

CLSmallExtentManager::~CLSmallExtentManager()
{
}

CLExtent * CLSmallExtentManager::GetAvailableExtent(size_t expectedSize, CLMetaDataManager * pMetadataManager)
{
	assert(pMetadataManager && expectedSize <= SMALL_MAX_SIZE);
	expectedSize = AlignSize(expectedSize);
	if (m_pCurrentExtent == nullptr)
	{
		SetCurrentExtent(expectedSize,pMetadataManager);
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
		pReturnExtent = SplitExtent(m_pCurrentExtent, expectedSize, pMetadataManager);
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

void CLSmallExtentManager::SetCurrentExtent(size_t expectedSize, CLMetaDataManager * pMetadataManager)
{
	if (m_pCurrentExtent != nullptr)
	{
		AppendExtent(m_pCurrentExtent);
		m_pCurrentExtent = nullptr;
	}

	unsigned int index = Size2Index(expectedSize);
	for (int i = index; i < SMALL_OBJECT_ARRAY_SIZE; ++i)
	{
		if ((m_pCurrentExtent = m_ExtentLists[i].GetExtent()) != nullptr)
		{
			break;
		}
	}

	if (m_pCurrentExtent == nullptr)
	{
		m_pCurrentExtent = MapANewExtent(pMetadataManager);
	}
}

void CLSmallExtentManager::AppendExtent(CLExtent * pExtent)
{
	assert(pExtent);
	unsigned int index = Size2Index(pExtent->GetSize());
	assert(index < SMALL_OBJECT_ARRAY_SIZE);
	m_ExtentLists[index].PutExtent(pExtent);
}

CLExtent * CLSmallExtentManager::MapANewExtent(CLMetaDataManager * pMetadataManager)
{
	assert(pMetadataManager);
	CLExtent * pExtent = pMetadataManager->GetExtent();
	if (pExtent == nullptr)
	{
		return nullptr;
	}
	void * pAddress = CLNVMMemoryMapManager::GetInstance()->MapMemory(SMALL_MAX_SIZE);
	if (pAddress == nullptr)
	{
		pMetadataManager->FreeExtent(pExtent);
		return nullptr;
	}

	pExtent->Init(pAddress, SMALL_MAX_SIZE, m_pLastExtent);
	m_pLastExtent = pExtent;
	return pExtent;
	//extent::merge判断是否在和自己合并，是不是在同一个arena中
	//small::merge判断合并后有没有超过最大值限制，超过了就不合并
}

CLExtent * CLSmallExtentManager::SplitExtent(CLExtent * pTargetExtent,size_t expectedSize, CLMetaDataManager * pMetadataManager)
{
	assert(pMetadataManager && pTargetExtent);
	CLExtent * pExtent = pMetadataManager->GetExtent();
	if (pExtent == nullptr)
	{
		return nullptr;
	}
	if (pTargetExtent->Split(pExtent, expectedSize) == nullptr)
	{
		pMetadataManager->FreeExtent(pExtent);
		return nullptr;
	}
	if (pTargetExtent == m_pLastExtent)
	{
		m_pLastExtent = pExtent;
	}
	return pExtent;
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