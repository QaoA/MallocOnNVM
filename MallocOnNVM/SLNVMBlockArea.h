#ifndef __NVM_BLOCK_AREA_H__
#define __NVM_BLOCK_AREA_H__

#include "SLList.h"
#include "SizeDefine.h"
#include "SLNVMBlock.h"

class CLBlockArea;

struct SLNVMBlockArea
{
	friend class CLBlockArea;
public:
	static unsigned int GetBlockCount();
	static unsigned int GetClassSize();

public:
	void Format(SLNVMBlockArea * pPrevious = nullptr);
	bool IsBlockBelongToSelf(SLNVMBlock * pBlock);
	SLNVMBlockArea * GetNextBlockAreaRecovery();
	
private:
	SLList m_list;
	SLNVMBlock m_pBlocks[1];
};

const unsigned int AREA_BLOCK_COUNT = (PAGE_SIZE - (sizeof(SLNVMBlockArea) - sizeof(SLNVMBlock))) / sizeof(SLNVMBlock);

#endif
