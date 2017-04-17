#include "CLExtent.h"
#include "SLNVMBlock.h"
#include "CLPerArenaBlockManager.h"
#include <cassert>

NS_BEGIN

CLExtent::CLExtent():
m_adjacentList(),
m_pNVMAddress(nullptr),
m_size(0),
m_arenaId(0),
m_pBlock(nullptr)
{
}

CLExtent::~CLExtent()
{
}

bool CLExtent::SetOccupied(CLPerArenaBlockManager * pBlockManager, unsigned int arenaId)
{
	assert(pBlockManager);
	m_pBlock = pBlockManager->AllocBlock();
	if (m_pBlock == nullptr)
	{
		return false;
	}
	m_arenaId = arenaId;
	m_pBlock->SetData(m_pNVMAddress, m_size, m_arenaId);
	return true;
}

void CLExtent::SetRelease(CLPerArenaBlockManager * pBlockManager)
{
	assert(pBlockManager);
	pBlockManager->FreeBlock(m_pBlock);
	m_pBlock = nullptr;
}

void CLExtent::AppendToAdjacentList(CLExtent * pPreviousExtent)
{
	if (pPreviousExtent != nullptr)
	{
		m_adjacentList.Append(&pPreviousExtent->m_adjacentList);
	}
}

void CLExtent::RemoveFromAdjacentList()
{
	m_adjacentList.Remove();
}

void CLExtent::Recovery(SLNVMBlock * pNVMBlock, CLBlockArea * pBlockArea)
{
	m_pBlock = new CLBlock(pNVMBlock, pBlockArea);
	m_pBlock->GetData(&m_pNVMAddress, &m_size, &m_arenaId);
}

void CLExtent::Recovery(void * pAddress, size_t size, int arenaId)
{
	m_pNVMAddress = pAddress;
	m_size = size;
	m_arenaId = arenaId;
	m_pBlock = nullptr;
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
	pNewExtent->m_adjacentList.Append(&m_adjacentList);
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



//void CLExtent::Recovery(SLNVMBlock * pNVMBlock, CLBlockArea * pBlockArea)
//{
//	assert(pNVMBlock);
//	m_pNVMBlock = pNVMBlock;
//	m_pNVMBlockOwner = pBlockArea;
//	m_pNVMAddress = m_pNVMBlock->GetNVMAddress();
//	m_size = m_pNVMBlock->GetSize();
//	m_arenaId = m_pNVMBlock->GetArenaId();
//}

NS_END