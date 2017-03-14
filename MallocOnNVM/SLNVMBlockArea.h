#ifndef __NVM_BLOCK_AREA_H__
#define __NVM_BLOCK_AREA_H__

#include "SLNVMList.h"
#include "SizeDefine.h"
#include "SLNVMBlock.h"

#define NVM_BLOCK_AREA_SIZE PAGE_SIZE

struct SLNVMBlockArea
{
public:
	static unsigned int GetBlockCount();

public:
	void Format(SLNVMBlockArea * pPrevious = nullptr);
	SLNVMBlockArea * GetNextBlockAreaRecovery();
	
public:
	struct SLData
	{
		SLNVMList m_list;
		SLNVMBlock m_pBlocks[1];
	};
	union
	{
		SLData m_data;
		char m_sizeArray[NVM_BLOCK_AREA_SIZE];
	};
};

const unsigned int AREA_BLOCK_COUNT = (sizeof(SLNVMBlockArea) - sizeof(SLNVMBlockArea::SLData) + sizeof(SLNVMBlock)) / sizeof(SLNVMBlock);

#endif
