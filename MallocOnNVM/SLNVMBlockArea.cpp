#include "SLNVMBlockArea.h"
#include "SLNVMBlock.h"
#include <cstring>
#include <cassert>

unsigned int SLNVMBlockArea::GetBlockCount()
{
	return AREA_BLOCK_COUNT;
}

void SLNVMBlockArea::Format(SLNVMBlockArea * pPrevious)
{
	for (int i = 0; i<AREA_BLOCK_COUNT; ++i)
	{
		m_data.m_pBlocks[i].Format();
	}
	if (pPrevious != nullptr)
	{
		m_data.m_list.Append(&pPrevious->m_data.m_list);
	}
	else
	{
		m_data.m_list.Init(&pPrevious->m_data.m_list);
	}
}

SLNVMBlockArea * SLNVMBlockArea::GetNextBlockAreaRecovery()
{
	return GetContainer(SLNVMBlockArea, m_data.m_list, m_data.m_list.GetNextRecovery());
}