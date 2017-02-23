#ifndef __EXTENT_H__
#define __EXTENT_H__

#include <cstddef>

struct SLNVMBlock;
class CLBlockArea;

class CLExtent
{
public:
	CLExtent();
	~CLExtent();

public:
	void SetOccupied(SLNVMBlock * pNVMBlock,CLBlockArea * pBlockOwner);
	void SetRelease();
	bool IsOccupied();
	CLBlockArea * GetBlockOwner();
	SLNVMBlock * GetNVMBlock();

public:
	CLExtent * Split(size_t anotherExtentSize);
	bool Merge(CLExtent * pAnotherExtent);

private:
	struct SLAdjacentList
	{
		SLAdjacentList();
		SLAdjacentList(CLExtent * pPrevious, CLExtent * pNext);
		CLExtent * m_pPreviousExtent;
		CLExtent * m_pNextExtent;
	}m_adjacentList;
	void * m_pNVMAddress;
	size_t m_size;
	SLNVMBlock * m_pNVMBlock;
	CLBlockArea * m_pNVMBlockOwner;
};

#endif
