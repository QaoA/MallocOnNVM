#ifndef __BLOCK_AREA_H__
#define __BLOCK_AREA_H__

#include <list>
#include "SLNVMBlockArea.h"

struct SLNVMBlock;
class CLBlock;
class CLRecoverier;

class CLBlockArea
{
public:
	CLBlockArea(SLNVMBlockArea * pNVMBlockArea);
	~CLBlockArea();

public:
	static unsigned int GetClassSize();

public:
	void Format(CLBlockArea * pPreviousArea = nullptr);
	CLBlock * GetAvailableBlock();
	void FreeBlock(CLBlock * pBlock);
	inline unsigned int GetFreeBlockCount();
	inline bool IsFull();
	inline bool IsEmpty();

public:
	int Recovery(CLRecoverier & recoverier);

private:
	SLNVMBlockArea * m_pNVMBlockArea;
	std::list<SLNVMBlock *> m_freeBlockList;
	unsigned int m_freeBlockCount;
};

unsigned int CLBlockArea::GetFreeBlockCount()
{
	return m_freeBlockCount;
}

bool CLBlockArea::IsFull()
{
	return m_freeBlockCount == 0;
}

bool CLBlockArea::IsEmpty()
{
	return m_freeBlockCount == SLNVMBlockArea::GetBlockCount();
}

#endif