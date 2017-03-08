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

void CLExtent::SetOccupied(SLNVMBlock * pNVMBlock, CLBlockArea * pBlockOwner, unsigned int arenaId)
{
	assert(pNVMBlock&&pBlockOwner);
	m_pNVMBlockOwner = pBlockOwner;
	m_pNVMBlock = pNVMBlock;
	m_arenaId = arenaId;
	m_pNVMBlock->SetData(m_pNVMAddress, m_size,arenaId);
}

void CLExtent::SetRelease()
{
	assert(m_pNVMBlock->GetReferenceCount() == 0);
	m_pNVMBlock = nullptr;
}

void CLExtent::SetAdjacentList(CLExtent * pPreviousExtent)
{
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

unsigned int CLExtent::GetArenaId()
{
	return m_arenaId;
}

void CLExtent::IncreaseReferenceCount()
{
	assert(m_pNVMBlock);
	m_pNVMBlock->IncreaseReferenceCount();
}

void CLExtent::DecreaseReferenceCount()
{
	assert(m_pNVMBlock);
	m_pNVMBlock->DecreaseReferenceCount();
}

void CLExtent::Recovery(SLNVMBlock * pNVMBlock, CLBlockArea * pBlockArea)
{
	assert(pNVMBlock);
	m_pNVMBlock = pNVMBlock;
	m_pNVMBlockOwner = pBlockArea;
	m_pNVMAddress = m_pNVMBlock->GetNVMAddress();
	m_size = m_pNVMBlock->GetSize();
	m_arenaId = m_pNVMBlock->GetArenaId();
}