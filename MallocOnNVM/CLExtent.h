#ifndef __EXTENT_H__
#define __EXTENT_H__

#include <cstddef>
#include "SLList.h"
#include "CLBlock.h"
#include <cassert>

class CLBlockArea;
class CLPerArenaBlockManager;

class CLExtent
{
public:
	CLExtent();
	~CLExtent();

public:
	bool SetOccupied(CLPerArenaBlockManager * pBlockManager, unsigned int arenaId);
	void SetRelease(CLPerArenaBlockManager * pBlockManager);
	void AppendToAdjacentList(CLExtent * pPreviousExtent);
	
public:	
	inline void SetAddress(void * pNVMAddress, size_t size);
	inline bool IsOccupied();
	inline size_t GetSize();
	inline CLExtent * GetAdjacentPreviousExtent();
	inline CLExtent * GetAdjacentNextExtent();
	inline void * GetNVMAddress();
	inline void * GetNVMEndAddress();
	inline unsigned int GetArenaId();
	inline void IncreaseReferenceCount();
	inline void DecreaseReferenceCount();


public:
	//void Recovery(SLNVMBlock * pNVMBlock, CLBlockArea * pBlockArea);

public:
	CLExtent * Split(CLExtent * pNewExtent,size_t anotherExtentSize);
	CLExtent * Merge(CLExtent * pAnotherExtent);
	bool CanMerge(CLExtent * pAnotherExtent);

private:
	bool CanSplit(size_t anotherExtentSize);

private:
	SLList m_adjacentList;
	void * m_pNVMAddress;
	size_t m_size;
	unsigned int m_arenaId;
	CLBlock * m_pBlock;
};

bool CLExtent::IsOccupied()
{
	return m_pBlock;
}

size_t CLExtent::GetSize()
{
	return m_size;
}
void CLExtent::SetAddress(void * pNVMAddress, size_t size)
{
	m_pNVMAddress = pNVMAddress;
	m_size = size;
}

CLExtent * CLExtent::GetAdjacentNextExtent()
{
	return GetContainer(CLExtent, m_adjacentList, m_adjacentList.m_pNext);
}

CLExtent * CLExtent::GetAdjacentPreviousExtent()
{
	return GetContainer(CLExtent, m_adjacentList, m_adjacentList.m_pPrevious);
}

void * CLExtent::GetNVMAddress()
{
	return m_pNVMAddress;
}

void * CLExtent::GetNVMEndAddress()
{
	return reinterpret_cast<void *>(reinterpret_cast<unsigned long>(m_pNVMAddress)+m_size);
}

unsigned int CLExtent::GetArenaId()
{
	return m_arenaId;
}

void CLExtent::IncreaseReferenceCount()
{
	assert(m_pBlock);
	m_pBlock->IncreaseReferenceCount();
}

void CLExtent::DecreaseReferenceCount()
{
	assert(m_pBlock);
	m_pBlock->DecreaseReferenceCount();
}

#endif
