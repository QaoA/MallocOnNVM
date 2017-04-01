#include "CLNVMMemoryMapManager.h"
#include <cstdlib>
#include <cassert>
#include <fcntl.h>
#include <unistd.h>
#include "CLSystemException.h"
#include "CLCriticalSection.h"
#include "CLBaseMetadata.h"
#include "CLExtent.h"
#include "CLExtentList.h"

CLNVMMemoryMapManager::CLNVMMemoryMapManager() :
m_fd(0),
m_pRecoveryBaseAddress(nullptr),
m_pBaseAddress(nullptr),
m_pLastAcquiredAddress(nullptr),
m_pBaseMetadata(nullptr),
m_pagesManager(),
m_mutex()
{
	m_fd = open("/home/mq/forNVMmalloc.txt", O_RDWR);
	if (m_fd == -1)
	{
		throw CLSystemException(FILE_OPEN_ERROR);
	}
	if ((m_pBaseAddress = mmap(const_cast<void *>(MMAP_BASE_ADDRESS), MMAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, m_fd, 0)) == MAP_FAILED)
	{
		throw CLSystemException(FILE_MAP_ERROR);
	}
	if (m_pBaseAddress != MMAP_BASE_ADDRESS)
	{
		throw CLSystemException(FILE_MAP_ADDRESS_ERROR);
	}
	m_pBaseMetadata = new CLBaseMetadata(static_cast<SLNVMBaseMetadata*>(m_pBaseAddress));
	m_pRecoveryBaseAddress = reinterpret_cast<void *>(reinterpret_cast<unsigned long>(m_pBaseAddress)+CLBaseMetadata::GetMetadataSize());
	m_pLastAcquiredAddress = m_pRecoveryBaseAddress;
}

CLNVMMemoryMapManager::~CLNVMMemoryMapManager()
{
	delete m_pBaseMetadata;
	munmap(m_pBaseAddress, MMAP_SIZE);
	close(m_fd);
}

CLNVMMemoryMapManager * CLNVMMemoryMapManager::GetInstance()
{
	static CLNVMMemoryMapManager instance;
	return &instance;
}

void * CLNVMMemoryMapManager::MapMemory(size_t size)
{
	assert((size &PAGE_SIZE_BIT) == 0);
	CLCriticalSection cs(&m_mutex);
	unsigned long pageCount = size >> PAGE_SIZE_BIT;
	void * pReturnAddress = nullptr;
	pReturnAddress = m_pagesManager.GetPages(pageCount);
	if (pReturnAddress == nullptr)
	{
		void * pNewLastAddress = reinterpret_cast<void *>(reinterpret_cast<unsigned long>(m_pLastAcquiredAddress)+size);
		if (pNewLastAddress > reinterpret_cast<void *>(reinterpret_cast<unsigned long>(m_pBaseAddress)+MMAP_SIZE))
		{
			return nullptr;
		}
		pReturnAddress = m_pLastAcquiredAddress;
		m_pLastAcquiredAddress = pNewLastAddress;
	}
	return pReturnAddress;
}

void CLNVMMemoryMapManager::UnmapMemory(CLExtent * pExtent)
{
	assert(pExtent);
	CLCriticalSection cs(&m_mutex);
	void * pAddress = pExtent->GetNVMAddress();
	size_t size = pExtent->GetSize();
	assert(size % PAGE_SIZE == 0);
	m_pagesManager.PutPages(pAddress, size / PAGE_SIZE);
}

void CLNVMMemoryMapManager::UnmapMemoryAndFreeExtent(CLExtentList * pExtentList, unsigned int unmapCount)
{
	assert(pExtentList && pExtentList->GetExtentCount() >= unmapCount);
	CLCriticalSection cs(&m_mutex);
	for (int i = 0; i < unmapCount; ++i)
	{
		CLExtent * pExtent = pExtentList->GetExtent();
		void * pAddress = pExtent->GetNVMAddress();
		size_t size = pExtent->GetSize();
		assert(size % PAGE_SIZE == 0);
		m_pagesManager.PutPages(pAddress, size / PAGE_SIZE);
		delete pExtent;
	}
}

void CLNVMMemoryMapManager::RecieveFreePages(void * pAddress, size_t size)
{
	assert(pAddress);
	assert(!(reinterpret_cast<unsigned long>(pAddress)&PAGE_SIZE_MASK));
	assert(!(size&PAGE_SIZE_MASK));
	m_pagesManager.PutPages(pAddress, size / PAGE_SIZE);
}