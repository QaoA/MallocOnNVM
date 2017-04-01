#ifndef __MEMORY_USE_INFO_H__
#define __MEMORY_USE_INFO_H__

#include "SizeDefine.h"
#include "CLExtent.h"
#include "CLBlockArea.h"

enum MEM_INFO_TYPE
{
	MEM_BLOCK,
	MEM_AREA,
	MEM_FREE,
	MEM_RESERVE
};

struct SLFreeInfo
{
public:
	SLFreeInfo(void * pAddress, unsigned int size);

public:
	inline void * GetNVMAddress();
	inline void * GetNVMEndAddress();
	inline int GetArenaId();

public:
	void * m_pAddress;
	unsigned int m_size;
};

typedef SLFreeInfo SLReservedArea;

struct SLMemoryUseInfo
{
public:
	SLMemoryUseInfo(CLExtent * pExtent);
	SLMemoryUseInfo(CLBlockArea * pArea);
	SLMemoryUseInfo(void * pAddress, unsigned int size);
	SLMemoryUseInfo(void * pReservedArea, unsigned int areaSize, bool reserveFlag);

public:
	inline MEM_INFO_TYPE GetType();
	inline unsigned long GetAddress();
	inline unsigned long GetEndAddress();
	inline int GetArenaId();

public:
	union
	{
		CLExtent * m_pExtent;
		CLBlockArea * m_pBlockArea;
		SLFreeInfo * m_pFreePage;
	};
	MEM_INFO_TYPE m_type;
};

void * SLFreeInfo::GetNVMAddress()
{
	return m_pAddress;
}

void * SLFreeInfo::GetNVMEndAddress()
{
	return reinterpret_cast<void *>(reinterpret_cast<unsigned long>(m_pAddress)+m_size);
}

int SLFreeInfo::GetArenaId()
{
	return -1;
}

MEM_INFO_TYPE SLMemoryUseInfo::GetType()
{
	return m_type;
}

unsigned long SLMemoryUseInfo::GetAddress()
{
	void * pAddress = nullptr;
	switch (m_type)
	{
	case MEM_BLOCK:
		pAddress = m_pExtent->GetNVMAddress();
		break;
	case MEM_AREA:
		pAddress = m_pBlockArea->GetNVMBaseAddress();
		break;
	case MEM_FREE:
		pAddress = m_pFreePage->GetNVMAddress();
		break;
	default:
		break;
	}
	return reinterpret_cast<unsigned long>(pAddress);
}

unsigned long SLMemoryUseInfo::GetEndAddress()
{
	void * pAddress = nullptr;
	switch (m_type)
	{
	case MEM_BLOCK:
		pAddress = m_pExtent->GetNVMEndAddress();
		break;
	case MEM_AREA:
		pAddress = m_pBlockArea->GetNVMEndAddress();
		break;
	case MEM_FREE:
		pAddress = m_pFreePage->GetNVMEndAddress();
		break;
	default:
		break;
	}
	return reinterpret_cast<unsigned long>(pAddress);
}

int SLMemoryUseInfo::GetArenaId()
{
	switch (m_type)
	{
	case MEM_BLOCK:
		return m_pExtent->GetArenaId();
		break;
	case MEM_AREA:
		return m_pBlockArea->GetArenaId();
		break;
	case MEM_FREE:
		return m_pFreePage->GetArenaId();
		break;
	default:
		break;
	}
}

#endif