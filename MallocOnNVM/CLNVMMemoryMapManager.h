#ifndef __NVM_MEMORY_MAP_MANAGER_H__
#define __NVM_MEMORY_MAP_MANAGER_H__

#include <cstddef>
#include <set>
#include "CLPageManager.h"
#include "CLMutex.h"

class CLExtentList;
class CLExtent;

const static char * FILE_PATH = "/home/mq/workspace/forNVMmalloc.txt";

class CLNVMMemoryMapManager
{
public:
	CLNVMMemoryMapManager();
	~CLNVMMemoryMapManager();

public:
	static CLNVMMemoryMapManager * GetInstance();

public:
	bool MapMemory(CLExtent * pExtent, size_t size);
	void * MapMemory(size_t size);
	void UnmapMemory(CLExtent * pExtent);
	void UnmapMemoryAndFreeExtent(CLExtentList * pExtentList, unsigned int unmapCount);

private:
	void SetPagesMapped(void * pAddress, size_t size);
	void SetPagesUnmapped(void * pAddress, size_t size);

private:
	int m_fd;
	void * m_pBaseAddress;
	void * m_pLastAcquiredAddress;
	CLPageManager m_pagesManager;
	CLMutex m_mutex;
};

#endif
