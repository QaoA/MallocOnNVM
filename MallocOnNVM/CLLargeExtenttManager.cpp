#include "CLLargeExtentManager.h"
#include "CLExtent.h"
#include "CLNVMMemoryMapManager.h"
#include <cassert>

CLLargeExtentManager::CLLargeExtentManager()
{
}

CLLargeExtentManager::~CLLargeExtentManager()
{
}

CLExtent * CLLargeExtentManager::GetAvailableExtent(size_t size)
{
	size = AlignSize(size);
	unsigned int index = Size2Index(size);
	CLExtent * pExtent = nullptr;
	pExtent = m_extentListArray[index].GetExtent();
	if (pExtent == nullptr)
	{
		for (int i = index + 1; i < LARGE_OBJECT_ARRAY_SIZE; ++i)
		{
			pExtent = m_extentListArray[i].GetExtent();
			if (pExtent != nullptr)
			{
				CLExtent * pNewExtent = new CLExtent();
				pExtent->Split(pNewExtent, size);
				AppendExtent(pExtent);
				return pNewExtent;
			}
		}
	}
	if (pExtent == nullptr)
	{
		return MapNewExtent(size);
	}
	return pExtent;
}

void CLLargeExtentManager::FreeExtent(CLExtent * pExtent)
{
	assert(pExtent);
	assert(pExtent->GetSize() >= LARGE_MIN_SIZE&&pExtent->GetSize() <= LARGE_MAX_SIZE);
	assert(pExtent->GetSize() == AlignSize(pExtent->GetSize()));
	AppendExtent(pExtent);
}

void CLLargeExtentManager::AppendExtent(CLExtent * pExtent)
{
	assert(pExtent);
	unsigned int index = Size2Index(pExtent->GetSize());
	m_extentListArray[index].PutExtent(pExtent);
	if (m_extentListArray[index].GetExtentCount() >= LARGE_OBJECT_MAX_CACHE_EXTENT_COUNT)
	{
		CLNVMMemoryMapManager::GetInstance()->UnmapMemoryAndFreeExtent(&m_extentListArray[index], 
			LARGE_OBJECT_MAX_CACHE_EXTENT_COUNT - (LARGE_OBJECT_MAX_CACHE_EXTENT_COUNT >> LARGE_OBJECT_CACHE_EXTENT_COUNT_PURGE_BIT));
	}
}

CLExtent * CLLargeExtentManager::MapNewExtent(size_t size)
{
	CLExtent * pExtent = new CLExtent();
	CLNVMMemoryMapManager::GetInstance()->MapMemory(pExtent, size);
	return pExtent;
}

unsigned int CLLargeExtentManager::Size2Index(size_t size)
{
	return size / PAGE_SIZE - 1;
}

size_t CLLargeExtentManager::AlignSize(size_t size)
{
	assert(size >= LARGE_MIN_SIZE&&size <= LARGE_MAX_SIZE);
	if (size%PAGE_SIZE != 0)
	{
		return ((size >> LARGE_OBJECT_ALIGN_BIT) + 1) << LARGE_OBJECT_ALIGN_BIT;
	}
	return size;
}