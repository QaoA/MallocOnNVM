#ifndef __NVM_MEMORY_MAP_MANAGER_H__
#define __NVM_MEMORY_MAP_MANAGER_H__

#include "cstddef"

class CLNVMMemoryMapManager
{
public:
	CLNVMMemoryMapManager();
	~CLNVMMemoryMapManager();

public:
	static CLNVMMemoryMapManager * GetInstance();

public:
	void * MapMemory(size_t size);
	void UnmapMemory(void * pAddress, size_t size);
};

#endif
