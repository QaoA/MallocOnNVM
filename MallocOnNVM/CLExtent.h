#ifndef __EXTENT_H__
#define __EXTENT_H__

#include <cstddef>
#include "SLList.h"

struct SLNVMBlock;
class CLBlockArea;

class CLExtent
{
public:
	CLExtent();
	~CLExtent();

public:
	void SetOccupied(SLNVMBlock * pNVMBlock,CLBlockArea * pBlockOwner,unsigned int arenaId);
	void SetRelease();
	void SetAdjacentList(CLExtent * pPreviousExtent);
	void SetAddress(void * pNVMAddress, size_t size);
	bool IsOccupied();
	CLBlockArea * GetBlockOwner();
	SLNVMBlock * GetNVMBlock();
	size_t GetSize();
	CLExtent * GetAdjacentPreviousExtent();
	CLExtent * GetAdjacentNextExtent();
	void * GetNVMAddress();
	void * GetNVMEndAddress();
	unsigned int GetArenaId();
	void IncreaseReferenceCount();
	void DecreaseReferenceCount();

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
	CLBlockArea * m_pNVMBlockOwner;
	unsigned int m_arenaId;
	SLNVMBlock * m_pNVMBlock;
};

#endif
