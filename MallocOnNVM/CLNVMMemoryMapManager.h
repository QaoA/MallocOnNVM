#ifndef __NVM_MEMORY_MAP_MANAGER_H__
#define __NVM_MEMORY_MAP_MANAGER_H__

#include <cstddef>
#include <set>
#include <sys/mman.h>
#include "CLPageManager.h"
#include "CLMutex.h"

class CLExtentList;
class CLExtent;
class CLBaseMetadata;

class CLNVMMemoryMapManager
{
public:
	CLNVMMemoryMapManager();
	~CLNVMMemoryMapManager();

public:
	static CLNVMMemoryMapManager * GetInstance();

public:
	void * MapMemory(size_t size);
	void UnmapMemory(CLExtent * pExtent);
	void UnmapMemoryAndFreeExtent(CLExtentList * pExtentList, unsigned int unmapCount);
	inline CLBaseMetadata * GetBaseMetadata();

public:
	void RecieveFreePages(void * pAddress, size_t size);
	void GetMemoryRecovery(void * pAddress, size_t size);

private:
	inline void SetPagesMapped(void * pAddress, size_t size);
	inline void SetPagesUnmapped(void * pAddress, size_t size);

private:
	int m_fd;
	void * m_pBaseAddress;
	void * m_pLastAcquiredAddress;
	CLBaseMetadata * m_pBaseMetadata;
	CLPageManager m_pagesManager;
	CLMutex m_mutex;
};

CLBaseMetadata * CLNVMMemoryMapManager::GetBaseMetadata()
{
	return m_pBaseMetadata;
}

void CLNVMMemoryMapManager::SetPagesMapped(void * pAddress, size_t size)
{
	madvise(pAddress, size, MADV_WILLNEED);
}

void CLNVMMemoryMapManager::SetPagesUnmapped(void * pAddress, size_t size)
{
	madvise(pAddress, size, MADV_DONTNEED);
}

#endif
