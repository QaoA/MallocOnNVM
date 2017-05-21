#include "CLSharedMemory.h"
#include "CLSystemException.h"
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

NS_BEGIN

CLSharedMemory::CLSharedMemory(const std::string & sharedMemoryName, const size_t sharedMemorySize, const void * mmapStartAddress):
m_sharedMemoryName(sharedMemoryName),
m_sharedMemorySize(sharedMemorySize),
m_mmapStartAddress(nullptr),
m_fd(-1)
{
	m_fd = shm_open(m_sharedMemoryName.c_str(), O_RDWR|O_CREAT, 00777);
	if (m_fd == -1)
	{
		throw CLSystemException(SHM_OPEN_ERROR);
	}
	
	int ret = ftruncate(m_fd, m_sharedMemorySize);
	if (ret == -1)
	{
		throw CLSystemException(SHM_TRUNCATE_ERROR);
	}

	m_mmapStartAddress = mmap(const_cast<void *>(mmapStartAddress), m_sharedMemorySize, PROT_READ | PROT_WRITE, MAP_SHARED, m_fd, 0);
	if (m_mmapStartAddress == MAP_FAILED)
	{
		throw CLSystemException(FILE_MAP_ERROR);
	}
	if (mmapStartAddress != nullptr && mmapStartAddress != m_mmapStartAddress)
	{
		throw CLSystemException(FILE_MAP_ADDRESS_ERROR);
	}
}

CLSharedMemory::~CLSharedMemory()
{
	munmap(m_mmapStartAddress, m_sharedMemorySize);
	shm_unlink(m_sharedMemoryName.c_str());
}

NS_END