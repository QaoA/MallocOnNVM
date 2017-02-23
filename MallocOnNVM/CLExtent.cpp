#include "CLExtent.h"
#include "SLNVMBlock.h"
#include <cassert>

CLExtent::SLAdjacentList::SLAdjacentList():
m_pPreviousExtent(nullptr),
m_pNextExtent(nullptr)
{
}

CLExtent::SLAdjacentList::SLAdjacentList(CLExtent * pPrevious, CLExtent * pNext) :
m_pPreviousExtent(pPrevious),
m_pNextExtent(pNext)
{
}

CLExtent::CLExtent():
m_adjacentList(),
m_pNVMAddress(nullptr),
m_size(0),
m_pNVMBlock(nullptr),
m_pNVMBlockOwner(nullptr)
{
}

CLExtent::~CLExtent()
{
}

void CLExtent::SetOccupied(SLNVMBlock * pNVMBlock,CLBlockArea * pBlockOwner)
{
	assert(pNVMBlock&&pBlockOwner);
	m_pNVMBlockOwner = pBlockOwner;
	m_pNVMBlock = pNVMBlock;
	m_pNVMBlock->SetAddress(m_pNVMAddress, m_size);
}

void CLExtent::SetRelease()
{
	m_pNVMAddress = nullptr;
	m_pNVMBlockOwner = nullptr;
}

bool CLExtent::IsOccupied()
{
	return m_pNVMBlock;
}

CLBlockArea * CLExtent::GetBlockOwner()
{
	return m_pNVMBlockOwner;
}

SLNVMBlock * CLExtent::GetNVMBlock()
{
	return m_pNVMBlock;
}