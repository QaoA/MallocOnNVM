#include "CLHugeExtentManager.h"
#include "SizeDefine.h"
#include "CLNVMMemoryMapManager.h"
#include "CLExtent.h"
#include <cassert>

CLHugeExtentManager::CLHugeExtentManager()
{
}

CLHugeExtentManager::~CLHugeExtentManager()
{
}

CLExtent * CLHugeExtentManager::GetAvailableExtent(size_t size)
{
	size = AlignSize(size);
	CLExtent * pExtent = new CLExtent();
	CLNVMMemoryMapManager::GetInstance()->MapMemory(pExtent,size);
	return pExtent;
}

void CLHugeExtentManager::FreeExtent(CLExtent * pExtent)
{
	assert(pExtent);
	CLNVMMemoryMapManager::GetInstance()->UnmapMemory(pExtent);
	delete pExtent;
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