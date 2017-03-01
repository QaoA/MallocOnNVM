#include "CLExtent.h"
#include "SLNVMBlock.h"
#include <cassert>

CLExtent::CLExtent():
m_adjacentList(),
m_pNVMAddress(nullptr),
m_size(0),
m_pNVMBlock(nullptr),
m_pNVMBlockOwner(nullptr),
m_arenaId(0)
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
	m_pNVMBlock = nullptr;
}

void CLExtent::Init(void * pNVMAddress, size_t size, CLExtent * pPreviousExtent)
{
	m_pNVMAddress = pNVMAddress;
	m_size = size;
	if (pPreviousExtent)
	{
		m_adjacentList.InitWithKnownNode(&pPreviousExtent->m_adjacentList);
	}
	else
	{
		m_adjacentList.InitDefault();
	}
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

size_t CLExtent::GetSize()
{
	return m_size;
}

CLExtent * CLExtent::Split(CLExtent * pNewExtent,size_t anotherExtentSize)
{
	assert(pNewExtent && anotherExtentSize);
	if (!CanSplit(anotherExtentSize))
	{
		return nullptr;
	}

	m_size -= anotherExtentSize;
	void * pNewNVMAddress = reinterpret_cast<void *>(reinterpret_cast<unsigned long>(m_pNVMAddress)+m_size);
	pNewExtent->SetAddress(pNewNVMAddress, anotherExtentSize);
	pNewExtent->m_adjacentList.AppendToList(&m_adjacentList);
	return pNewExtent;
}

CLExtent * CLExtent::Merge(CLExtent * pAnotherExtent)
{
	assert(pAnotherExtent&&CanMerge(pAnotherExtent));
	m_pNVMAddress = m_pNVMAddress > (pAnotherExtent->m_pNVMAddress) ? (pAnotherExtent->m_pNVMAddress) : m_pNVMAddress;
	m_size += pAnotherExtent->m_size;
	pAnotherExtent->m_adjacentList.Remove();
	return this;
}

bool CLExtent::CanSplit(size_t anotherExtentSize)
{
	return m_size > anotherExtentSize;
}

bool CLExtent::CanMerge(CLExtent * pAnotherExtent)
{
	assert(pAnotherExtent);
	if (IsOccupied() || pAnotherExtent->IsOccupied())
	{
		return false;
	}
	return (reinterpret_cast<unsigned long>(m_pNVMAddress)+static_cast<unsigned long>(m_size) == reinterpret_cast<unsigned long>(pAnotherExtent->m_pNVMAddress)) ||
		(reinterpret_cast<unsigned long>(pAnotherExtent->m_pNVMAddress) + static_cast<unsigned long>(pAnotherExtent->m_size) == reinterpret_cast<unsigned long>(m_pNVMAddress));
}

void CLExtent::SetAddress(void * pNVMAddress, size_t size)
{
	m_pNVMAddress = pNVMAddress;
	m_size = size;
}

CLExtent * CLExtent::GetAdjacentNextExtent()
{
	return GetContainer(CLExtent, m_adjacentList, m_adjacentList.GetNext());
}

CLExtent * CLExtent::GetAdjacentPreviousExtent()
{
	return GetContainer(CLExtent, m_adjacentList, m_adjacentList.GetPrevious());
}

void * CLExtent::GetNVMAddress()
{
	return m_pNVMAddress;
}

void * CLExtent::GetNVMEndAddress()
{
	return reinterpret_cast<void *>(reinterpret_cast<unsigned long>(m_pNVMAddress)+m_size);
}