#ifndef __NVM_BLOCK_H__
#define __NVM_BLOCK_H__

#include "NVMMallocNameSpace.h"
#include <cstddef>

NS_BEGIN

struct SLNVMBlock
{
public:
	inline bool IsAvailable();
	inline void SetData(void * pAddress, size_t size, unsigned int arenaId);
	inline void Format();
	inline void IncreaseReferenceCount();
	inline void DecreaseReferenceCount();
	inline unsigned int * GetNVMReferenceCountAddress();
	inline int GetArenaId();

public:
	unsigned int m_referenceCount;
	size_t m_size;
	void * m_pAddress;
	unsigned int m_arenaId;
};

void SLNVMBlock::SetData(void * pAddress, size_t size, unsigned int arenaId)
{
	m_pAddress = pAddress;
	m_size = size;
	m_arenaId = arenaId;
}

bool SLNVMBlock::IsAvailable()
{
	return !m_referenceCount;
}

void SLNVMBlock::Format()
{
	m_referenceCount = 0;
}

void SLNVMBlock::IncreaseReferenceCount()
{
	++m_referenceCount;
}

void SLNVMBlock::DecreaseReferenceCount()
{
	--m_referenceCount;
}

inline unsigned int * SLNVMBlock::GetNVMReferenceCountAddress()
{
	return &m_referenceCount;
}

int SLNVMBlock::GetArenaId()
{
	return m_arenaId;
}

NS_END
#endif