#include "SLNVMBlockArea.h"
#include "SLNVMBlock.h"
#include <cstring>

unsigned int SLNVMBlockArea::GetBlockCount()
{
	return AREA_BLOCK_COUNT;
}

unsigned int SLNVMBlockArea::GetClassSize()
{
	return PAGE_SIZE;
}

void SLNVMBlockArea::Format(SLNVMBlockArea * pPrevious)
{
	if (pPrevious)
	{
		m_list.InitWithKnownNode(&pPrevious->m_list);
	}
	else
	{
		m_list.InitDefault();
	}
	memset(&this->m_pBlocks[0], 0, GetBlockCount() * sizeof(SLNVMBlock));
}

bool SLNVMBlockArea::IsBlockBelongToSelf(SLNVMBlock * pBlock)
{
	return (reinterpret_cast<unsigned long>(pBlock) > reinterpret_cast<unsigned long>(this)) &&
		(reinterpret_cast<unsigned long>(pBlock) < (reinterpret_cast<unsigned long>(this) + GetClassSize()));
}