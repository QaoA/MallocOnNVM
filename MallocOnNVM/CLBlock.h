#ifndef __BLOCK_H__
#define __BLOCK_H__

#include "SLNVMBlock.h"
#include <cassert>

class CLBlockArea;
class CLExtent;

class CLBlock
{
	friend class CLBlockArea;
public:
	CLBlock(SLNVMBlock * pNVMBlock,CLBlockArea * pOwner);
	~CLBlock();

public:
	inline void SetData(void * pNVMAddress, size_t size, unsigned int arenaId);
	inline void GetData(void ** ppNVMAddress, size_t * pSize, unsigned int * pArenaId);
	inline CLBlockArea * GetOwner();
	inline void IncreaseReferenceCount();
	inline void DecreaseReferenceCount();

private:
	SLNVMBlock * m_pNVMBlock;
	CLBlockArea * m_owner;
};

void CLBlock::SetData(void * pNVMAddress, size_t size, unsigned int arenaId)
{
	m_pNVMBlock->m_arenaId = arenaId;
	m_pNVMBlock->m_pAddress = pNVMAddress;
	m_pNVMBlock->m_size = size;
}

void CLBlock::GetData(void ** ppNVMAddress, size_t * pSize, unsigned int * pArenaId)
{
	assert(ppNVMAddress && pSize && pArenaId);
	*ppNVMAddress = m_pNVMBlock->m_pAddress;
	*pSize = m_pNVMBlock->m_size;
	*pArenaId = m_pNVMBlock->m_arenaId;
}

CLBlockArea * CLBlock::GetOwner()
{
	return m_owner;
}

void CLBlock::IncreaseReferenceCount()
{
	m_pNVMBlock->IncreaseReferenceCount();
}

void CLBlock::DecreaseReferenceCount()
{
	m_pNVMBlock->DecreaseReferenceCount();
}

#endif