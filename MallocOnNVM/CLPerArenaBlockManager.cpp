#include "CLPerArenaBlockManager.h"
#include "CLGlobalBlockAreaManager.h"
#include "CLBlockArea.h"
#include "CLBlock.h"
#include <cassert>
#include <algorithm>

NS_BEGIN

using namespace std;

CLPerArenaBlockManager::CLPerArenaBlockManager():
m_nonFullAreaList(),
m_fullAreaList(),
m_emptyAreaList(),
m_emptyAreaCount(0)
{
}

CLPerArenaBlockManager::~CLPerArenaBlockManager()
{
}

CLBlock * CLPerArenaBlockManager::AllocBlock()
{
	if (m_nonFullAreaList.empty())
	{
		if (m_emptyAreaList.empty())
		{
			CLBlockArea * pArea = CLGlobalBlockAreaManager::GetInstance()->GetABlockArea();
			if (pArea == nullptr)
			{
				return nullptr;
			}
			m_nonFullAreaList.push_back(pArea);
		}
		else
		{
			m_nonFullAreaList.push_back(m_emptyAreaList.front());
			m_emptyAreaList.pop_front();
			m_emptyAreaCount--;
		}
	}
	assert(!m_nonFullAreaList.empty());
	CLBlockArea * pArea = m_nonFullAreaList.front();
	CLBlock * pBlock = pArea->GetAvailableBlock();
	if (pArea->IsFull())
	{
		m_nonFullAreaList.pop_front();
		m_fullAreaList.push_back(pArea);
	}
	return pBlock;
}

void CLPerArenaBlockManager::FreeBlock(CLBlock * pBlock)
{
	assert(pBlock);
	CLBlockArea * pArea = pBlock->GetOwner();
	if (pArea->IsFull())
	{
		m_fullAreaList.erase(find(m_fullAreaList.begin(),m_fullAreaList.end(),pArea));
		m_nonFullAreaList.push_back(pArea);
	}
	pArea->FreeBlock(pBlock);
	if (pArea->IsEmpty())
	{
		m_nonFullAreaList.erase(find(m_nonFullAreaList.begin(), m_nonFullAreaList.end(), pArea));
		m_emptyAreaList.push_back(pArea);
		m_emptyAreaCount++;
		if (m_emptyAreaCount > CACHE_EMPTY_AREA_MAX_COUNT)
		{
			unsigned int purgeCount = m_emptyAreaCount - CACHE_EMPTY_AREA_MAX_COUNT >> EMPTY_AREA_PURGE_BIT;
			CLGlobalBlockAreaManager::GetInstance()->FreeBlockAreas(m_emptyAreaList, purgeCount);
			m_emptyAreaCount = CACHE_EMPTY_AREA_MAX_COUNT >> EMPTY_AREA_PURGE_BIT;
		}
	}
}

void CLPerArenaBlockManager::RecieveBlockAreaRecovery(CLBlockArea * pBlockArea)
{
	assert(pBlockArea && !pBlockArea->IsEmpty());
	if (pBlockArea->IsFull())
	{
		m_fullAreaList.push_back(pBlockArea);
	}
	else
	{
		m_nonFullAreaList.push_back(pBlockArea);
	}
}

NS_END