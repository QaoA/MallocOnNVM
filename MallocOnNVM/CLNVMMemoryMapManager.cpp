#include "CLNVMMemoryMapManager.h"
#include <cstdlib>

CLNVMMemoryMapManager::CLNVMMemoryMapManager()
{
}


CLNVMMemoryMapManager::~CLNVMMemoryMapManager()
{
}

CLNVMMemoryMapManager * CLNVMMemoryMapManager::GetInstance()
{
	static CLNVMMemoryMapManager instance;
	return &instance;
}

void * CLNVMMemoryMapManager::MapMemory(size_t size)
{
	return malloc(size);
}

void CLNVMMemoryMapManager::UnmapMemory(void * pAddress, size_t size)
{
	free(pAddress);
}