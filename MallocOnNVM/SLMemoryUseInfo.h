#ifndef __MEMORY_USE_INFO_H__
#define __MEMORY_USE_INFO_H__

#include "SizeDefine.h"

struct SLMemoryUseInfo
{
public:
	inline unsigned long GetBeginBoundary();
	inline unsigned long GetEndBoundary();

public:
	void * m_pAddress;
	size_t m_size;
	int m_arenaId;
	bool m_bIsBlockArea;
};

unsigned long SLMemoryUseInfo::GetBeginBoundary()
{
	return reinterpret_cast<unsigned long>(m_pAddress & (~PAGE_SIZE_MASK));
}

unsigned long SLMemoryUseInfo::GetEndBoundary()
{
	unsigned long tmpBoundary = (reinterpret_cast<unsigned long>(m_pAddress)+m_size);
	if ((tmpBoundary & PAGE_SIZE_MASK) == 0)
	{
		return tmpBoundary;
	}
	return (tmpBoundary&PAGE_SIZE_MASK) + PAGE_SIZE;
}

#endif