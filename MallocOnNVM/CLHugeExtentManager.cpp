#include "CLHugeExtentManager.h"
#include "SizeDefine.h"
#include "CLNVMMemoryMapManager.h"
#include <cassert>

CLHugeExtentManager::CLHugeExtentManager()
{
}

CLHugeExtentManager::~CLHugeExtentManager()
{
}

CLExtent * CLHugeExtentManager::GetAvailableExtent(size_t size,CLMetaDataManager * pMetadataManager)
{
	assert(pMetadataManager);
	size = AlignSize(size);
	CLExtent * pExtent = pMetadataManager->GetExtent();
	CLNVMMemoryMapManager::GetInstance()->MapMemory(pExtent,size);
	return pExtent;
}

void CLHugeExtentManager::FreeExtent(CLExtent * pExtent, CLMetaDataManager * pMetadataManager)
{
	assert(pExtent && pMetadataManager);
	CLNVMMemoryMapManager::GetInstance()->UnmapMemory(pExtent);
	pMetadataManager->FreeExtent(pExtent);
}

size_t CLHugeExtentManager::AlignSize(size_t size)
{
	assert(size >= HUGE_OBJECT_MIN_SIZE);
	if (size%PAGE_SIZE != 0)
	{
		return ((size >> LARGE_OBJECT_ALIGN_BIT) + 1) << LARGE_OBJECT_ALIGN_BIT;
	}
	return size;
}