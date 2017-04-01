#ifndef __NVM_MEMORY_MAP_MANAGER_H__
#define __NVM_MEMORY_MAP_MANAGER_H__

#include <cstddef>
#include <set>
#include <sys/mman.h>
#include "CLPageManager.h"
#include "CLMutex.h"
#include "SizeDefine.h"

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
	inline void * GetRecoveryBaseAddress();
	inline void RecieveLastMapAddressRecovery(void * pAddress);

private:
	int m_fd;
	void * m_pRecoveryBaseAddress;
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

void * CLNVMMemoryMapManager::GetRecoveryBaseAddress()
{
	return m_pRecoveryBaseAddress;
}

void CLNVMMemoryMapManager::RecieveLastMapAddressRecovery(void * pAddress)
{
	m_pLastAcquiredAddress = pAddress;
}

#endif
