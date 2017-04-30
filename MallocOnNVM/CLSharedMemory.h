#ifndef __SHARED_MEMORY_H__
#define __SHARED_MEMORY_H__

#include <cstddef>
#include <string>
#include "NVMMallocNameSpace.h"

NS_BEGIN

class CLSharedMemory
{
public:
	CLSharedMemory(const std::string & sharedMemoryName, const size_t sharedMemorySize, const void * mmapStartAddress);
	~CLSharedMemory();

public:
	inline void * GetMappedAddress();

private:
	void * m_mmapStartAddress;
	int m_fd;
	std::string m_sharedMemoryName;
	size_t m_sharedMemorySize;
};

inline void * CLSharedMemory::GetMappedAddress()
{
	return m_mmapStartAddress;
}

NS_END

#endif