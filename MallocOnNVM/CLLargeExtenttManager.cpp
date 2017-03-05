#include "CLLargeExtentManager.h"
#include "CLMetaDataManager.h"
#include "CLExtent.h"
#include "CLNVMMemoryMapManager.h"
#include <cassert>

CLLargeExtentManager::CLLargeExtentManager()
{
}

CLLargeExtentManager::~CLLargeExtentManager()
{
}

CLExtent * CLLargeExtentManager::GetAvailableExtent(size_t size,CLMetaDataManager * pMetadataManager)
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
				CLExtent * pNewExtent = pMetadataManager->GetExtent();
				pExtent->Split(pNewExtent, size);
				AppendExtent(pExtent,pMetadataManager);
				return pNewExtent;
			}
		}
	}
	if (pExtent == nullptr)
	{
		return MapNewExtent(size, pMetadataManager);
	}
	return pExtent;
}

void CLLargeExtentManager::FreeExtent(CLExtent * pExtent,CLMetaDataManager * pMetadataManager)
{
	assert(pExtent&&pMetadataManager);
	assert(pExtent->GetSize() >= LARGE_MIN_SIZE&&pExtent->GetSize() <= LARGE_MAX_SIZE);
	assert(pExtent->GetSize() == AlignSize(pExtent->GetSize()));
	AppendExtent(pExtent,pMetadataManager);
}

void CLLargeExtentManager::AppendExtent(CLExtent * pExtent, CLMetaDataManager * pMetadataManager)
{
	assert(pExtent && pMetadataManager);
	unsigned int index = Size2Index(pExtent->GetSize());
	m_extentListArray[index].PutExtent(pExtent);
	if (m_extentListArray[index].GetExtentCount() >= LARGE_OBJECT_MAX_CACHE_EXTENT_COUNT)
	{
		CLNVMMemoryMapManager::GetInstance()->UnmapMemoryAndFreeExtent(&m_extentListArray[index], 
			LARGE_OBJECT_MAX_CACHE_EXTENT_COUNT - (LARGE_OBJECT_MAX_CACHE_EXTENT_COUNT >> LARGE_OBJECT_CACHE_EXTENT_COUNT_PURGE_BIT),
			pMetadataManager);
	}
}

CLExtent * CLLargeExtentManager::MapNewExtent(size_t size, CLMetaDataManager * pMetadataManager)
{
	CLExtent * pExtent = pMetadataManager->GetExtent();
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