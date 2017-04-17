#include "CLBlockArea.h"
#include "SLNVMBlockArea.h"
#include "CLRecoverier.h"
#include "CLBlock.h"
#include <cassert>

NS_BEGIN

CLBlockArea::CLBlockArea(SLNVMBlockArea * pNVMBlockArea) :
m_pNVMBlockArea(pNVMBlockArea),
m_freeBlockList(),
m_freeBlockCount(0),
m_arenaId(-1)
{
}

CLBlockArea::~CLBlockArea()
{
}

unsigned int CLBlockArea::GetClassSize()
{
	return sizeof(SLNVMBlockArea);
}

void CLBlockArea::Format(CLBlockArea * pPreviousArea)
{
	if (pPreviousArea == nullptr)
	{
		m_pNVMBlockArea->Format();
	}
	else
	{
		m_pNVMBlockArea->Format(pPreviousArea->m_pNVMBlockArea);
	}

	m_freeBlockCount = SLNVMBlockArea::GetBlockCount();
	for (int i = 0; i < m_freeBlockCount; ++i)
	{
		m_freeBlockList.push_back(&m_pNVMBlockArea->m_data.m_pBlocks[i]);
	}
}

CLBlock * CLBlockArea::GetAvailableBlock()
{
	if (m_freeBlockCount == 0)
	{
		return nullptr;
	}

	m_freeBlockCount--;
	SLNVMBlock * pReturnBlock = m_freeBlockList.back();
	m_freeBlockList.pop_back();
	return new CLBlock(pReturnBlock, this);
}

void CLBlockArea::FreeBlock(CLBlock * pBlock)
{
	assert(pBlock);
	m_freeBlockList.push_back(pBlock->m_pNVMBlock);
	m_freeBlockCount++;
	delete pBlock;
}

void CLBlockArea::Recovery(CLRecoverier & recoverier)
{
	unsigned int blockCount = SLNVMBlockArea::GetBlockCount();
	for (int i = 0; i < blockCount; ++i)
	{
		if (m_pNVMBlockArea->m_data.m_pBlocks[i].IsAvailable())
		{
			m_freeBlockList.push_back(&m_pNVMBlockArea->m_data.m_pBlocks[i]);
			m_freeBlockCount++;
		}
		else
		{
			if (m_arenaId == -1)
			{
				m_arenaId = m_pNVMBlockArea->m_data.m_pBlocks[i].GetArenaId();
			}
			assert(m_arenaId == m_pNVMBlockArea->m_data.m_pBlocks[i].GetArenaId());
			recoverier.AppendInfo(&m_pNVMBlockArea->m_data.m_pBlocks[i],this);
		}
	}
}

NS_END