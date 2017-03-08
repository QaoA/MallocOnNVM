#ifndef __BLOCK_AREA_H__
#define __BLOCK_AREA_H__

#include <list>
#include "SLList.h"

struct SLNVMBlockArea;
struct SLNVMBlock;
class CLRecoverier;

class CLBlockArea
{
public:
	CLBlockArea();
	~CLBlockArea();

public:
	void Format(SLNVMBlockArea * pNVMBlockArea);
	void Format(SLNVMBlockArea * pNVMBlockArea, CLBlockArea * pPreviousArea);
	void Recovery(SLNVMBlockArea * pNVMBlockArea,CLRecoverier * pRecoverier);
	SLNVMBlock * GetAvailableBlock();
	void FreeBlock(SLNVMBlock * pNVMBlock);
	void LinkToList(CLBlockArea * pPreviousArea);
	unsigned int GetFreeBlockCount();
	bool IsFull();

private:
	bool IsBlockBelongToSelf(SLNVMBlock * pNVMBlock);

private:
	SLList m_list;
	SLNVMBlockArea * m_pNVMBlockArea;
	std::list<SLNVMBlock *> m_freeBlockList;
	unsigned int m_freeBlockCount;
};

#endif