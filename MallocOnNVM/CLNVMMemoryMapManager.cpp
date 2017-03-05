#include "CLNVMMemoryMapManager.h"
#include <cstdlib>
#include <sys/mman.h>
#include <cassert>
#include "SizeDefine.h"
#include "CLSystemException.h"
#include "CLExtent.h"
#include "CLExtentList.h"
#include "CLCriticalSection.h"
#include "CLMetaDataManager.h"

CLNVMMemoryMapManager::CLNVMMemoryMapManager():
m_fd(0),
m_pBaseAddress(nullptr),
m_pLastAcquiredAddress(nullptr),
m_pagesManager(),
m_mutex()
{
	if ((m_pBaseAddress = mmap(const_cast<void *>(MMAP_BASE_ADDRESS), MMAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0)) == MAP_FAILED)
	{
		throw CLSystemException(FILE_MAP_ERROR);
	}
	if (m_pBaseAddress != MMAP_BASE_ADDRESS)
	{
		throw CLSystemException(FILE_MAP_ADDRESS_ERROR);
	}
	madvise(m_pBaseAddress, MMAP_SIZE, MADV_DONTNEED);
	m_pLastAcquiredAddress = m_pBaseAddress;
}

CLNVMMemoryMapManager::~CLNVMMemoryMapManager()
{
	munmap(m_pBaseAddress, MMAP_SIZE);
}

CLNVMMemoryMapManager * CLNVMMemoryMapManager::GetInstance()
{
	static CLNVMMemoryMapManager instance;
	return &instance;
}

bool CLNVMMemoryMapManager::MapMemory(CLExtent * pExtent, size_t size)
{
	assert(pExtent);
	void * pAddress = MapMemory(size);
	if (pAddress == nullptr)
	{
		return false;
	}
	pExtent->SetAddress(pAddress, size);
	return true;
}

void * CLNVMMemoryMapManager::MapMemory(size_t size)
{
	CLCriticalSection cs(&m_mutex);
	assert(size % PAGE_SIZE == 0);
	void * pReturnAddress = nullptr;
	pReturnAddress = m_pagesManager.GetPages(size / PAGE_SIZE);
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
	SetPagesMapped(pReturnAddress, size);
	return pReturnAddress;
}

void CLNVMMemoryMapManager::UnmapMemory(CLExtent * pExtent)
{
	assert(pExtent);
	CLCriticalSection cs(&m_mutex);
	void * pAddress = pExtent->GetNVMAddress();
	size_t size = pExtent->GetSize();
	assert(size % PAGE_SIZE == 0);
	SetPagesUnmapped(pAddress, size);
	m_pagesManager.PutPages(pAddress, size / PAGE_SIZE);
}

void CLNVMMemoryMapManager::UnmapMemoryAndFreeExtent(CLExtentList * pExtentList, unsigned int unmapCount, CLMetaDataManager * pMetadataManager)
{
	assert(pExtentList && pExtentList->GetExtentCount() >= unmapCount && pMetadataManager);
	CLCriticalSection cs(&m_mutex);
	for (int i = 0; i < unmapCount; ++i)
	{
		CLExtent * pExtent = pExtentList->GetExtent();
		void * pAddress = pExtent->GetNVMAddress();
		size_t size = pExtent->GetSize();
		assert(size % PAGE_SIZE == 0);
		SetPagesUnmapped(pAddress, size);
		m_pagesManager.PutPages(pAddress, size / PAGE_SIZE);
		pMetadataManager->FreeExtent(pExtent);
	}
}

void CLNVMMemoryMapManager::SetPagesMapped(void * pAddress, size_t size)
{
	madvise(pAddress, size, MADV_WILLNEED);
}

void CLNVMMemoryMapManager::SetPagesUnmapped(void * pAddress, size_t size)
{
	madvise(pAddress, size, MADV_DONTNEED);
}