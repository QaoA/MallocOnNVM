#include "CLBlockArea.h"
#include "SLNVMBlockArea.h"
#include <cassert>

CLBlockArea::CLBlockArea():
m_list(),
m_pNVMBlockArea(nullptr),
m_freeBlockList(),
m_freeBlockCount(0)
{
}

CLBlockArea::~CLBlockArea()
{
}

void CLBlockArea::Format(SLNVMBlockArea * pNVMBlockArea)
{
	Format(pNVMBlockArea, nullptr);
}

void CLBlockArea::Format(SLNVMBlockArea * pNVMBlockArea, CLBlockArea * pPreviousArea)
{
	assert(pNVMBlockArea);
	m_pNVMBlockArea = pNVMBlockArea;

	if (pPreviousArea == nullptr)
	{
		m_list.InitDefault();
		m_pNVMBlockArea->Format();
	}
	else
	{
		m_list.InitWithKnownNode(&pPreviousArea->m_list);
		m_pNVMBlockArea->Format(pPreviousArea->m_pNVMBlockArea);
	}

	m_freeBlockCount = SLNVMBlockArea::GetBlockCount();
	for (int i = 0; i < m_freeBlockCount; ++i)
	{
		m_freeBlockList.push_back(&m_pNVMBlockArea->m_pBlocks[i]);
	}
}

SLNVMBlock * CLBlockArea::GetAvailableBlock()
{
	if (m_freeBlockCount == 0)
	{
		return nullptr;
	}

	m_freeBlockCount--;
	SLNVMBlock * pReturnBlock = m_freeBlockList.back();
	m_freeBlockList.pop_back();
	return pReturnBlock;
}

void CLBlockArea::FreeBlock(SLNVMBlock * pNVMBlock)
{
	assert(pNVMBlock && IsBlockBelongToSelf(pNVMBlock));
	
	m_freeBlockList.push_back(pNVMBlock);
	m_freeBlockCount++;
}

void CLBlockArea::LinkToList(CLBlockArea * pPreviousArea)
{
	if (pPreviousArea)
	{
		m_list.LinkToList(&pPreviousArea->m_list);
		m_pNVMBlockArea->m_list.LinkToList(&pPreviousArea->m_pNVMBlockArea->m_list);
	}
}

unsigned int CLBlockArea::GetFreeBlockCount()
{
	return m_freeBlockCount;
}

bool CLBlockArea::IsFull()
{
	return GetFreeBlockCount() == SLNVMBlockArea::GetBlockCount();
}

bool CLBlockArea::IsBlockBelongToSelf(SLNVMBlock * pNVMBlock)
{
	return m_pNVMBlockArea->IsBlockBelongToSelf(pNVMBlock);
}