#ifndef __NVM_MEMORY_MAP_MANAGER_H__
#define __NVM_MEMORY_MAP_MANAGER_H__

#include <cstddef>
#include <set>
#include "CLPageManager.h"

const static char * FILE_PATH = "/home/mq/workspace/forNVMmalloc.txt";

class CLNVMMemoryMapManager
{
public:
	struct SLPAGES
	{
		void * m_pAddress;
		unsigned int m_pageCount;
	};

public:
	CLNVMMemoryMapManager();
	~CLNVMMemoryMapManager();

public:
	static CLNVMMemoryMapManager * GetInstance();

public:
	void * MapMemory(size_t size);
	void UnmapMemory(void * pAddress, size_t size);

private:
	void SetPagesMapped(void * pAddress, size_t size);
	void SetPagesUnmapped(void * pAddress, size_t size);

private:
	int m_fd;
	void * m_pBaseAddress;
	void * m_pLastAcquiredAddress;
	CLPageManager m_pagesManager;
};

#endif
