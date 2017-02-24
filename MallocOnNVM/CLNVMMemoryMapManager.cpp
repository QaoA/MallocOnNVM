#include "CLNVMMemoryMapManager.h"
#include <cstdlib>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <cassert>
#include "SizeDefine.h"
#include "CLSystemException.h"

CLNVMMemoryMapManager::CLNVMMemoryMapManager():
m_fd(0),
m_pBaseAddress(nullptr),
m_pLastAcquiredAddress(nullptr),
m_pagesManager()
{
	m_fd = open(FILE_PATH, O_RDWR | O_CREAT);
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
	madvise(m_pBaseAddress, MMAP_SIZE, MADV_DONTNEED);
	m_pLastAcquiredAddress = m_pBaseAddress;
}

CLNVMMemoryMapManager::~CLNVMMemoryMapManager()
{
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
		return pReturnAddress;
	}
	SetPagesMapped(pReturnAddress, size);
	return pReturnAddress;
}

void CLNVMMemoryMapManager::UnmapMemory(void * pAddress, size_t size)
{
	assert(size % PAGE_SIZE == 0);
	SetPagesUnmapped(pAddress, size);
	m_pagesManager.PutPages(pAddress, size / PAGE_SIZE);
}

CLNVMMemoryMapManager::SLPAGES * CLNVMMemoryMapManager::TryMapFromSet(size_t size)
{

}

void CLNVMMemoryMapManager::SetPagesMapped(void * pAddress, size_t size)
{
	madvise(pAddress, size, MADV_DONTNEED);
}

void CLNVMMemoryMapManager::SetPagesUnmapped(void * pAddress, size_t size)
{
	madvise(pAddress, size, MADV_WILLNEED);
}