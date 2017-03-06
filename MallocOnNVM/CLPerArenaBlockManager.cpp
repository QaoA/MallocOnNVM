#include "CLPerArenaBlockManager.h"
#include "CLGlobalBlockAreaManager.h"
#include "CLExtent.h"
#include "CLBlockArea.h"
#include <cassert>

using namespace std;

CLPerArenaBlockManager::CLPerArenaBlockManager():
m_NonFullAreaList(),
m_FullAreaList(),
m_nonFullAreasCount(0)
{
}

CLPerArenaBlockManager::~CLPerArenaBlockManager()
{
}

CLExtent * CLPerArenaBlockManager::AllocBlockForExtent(CLExtent * pExtent, unsigned int arenaId)
{
	if (m_nonFullAreasCount == 0)
	{
		CLBlockArea * pArea = CLGlobalBlockAreaManager::GetInstance()->GetABlockArea();
		if (pArea == nullptr)
		{
			return nullptr;
		}
		m_NonFullAreaList.push_back(pArea);
		m_nonFullAreasCount++;
	}
	CLBlockArea * pCurrentArea = m_NonFullAreaList.front();
	pExtent->SetOccupied(pCurrentArea->GetAvailableBlock(), pCurrentArea, arenaId);
	if (pCurrentArea->GetFreeBlockCount() == 0)
	{
		m_NonFullAreaList.pop_front();
		m_nonFullAreasCount--;
		m_FullAreaList.push_back(pCurrentArea);
	}
	return pExtent;
}

void CLPerArenaBlockManager::FreeBlockForExtent(CLExtent * pExtent)
{
	assert(pExtent&&pExtent->IsOccupied());
	CLBlockArea * pBlockOwner = pExtent->GetBlockOwner();
	assert(pBlockOwner);
	if (pBlockOwner->IsFull())
	{
		for (list<CLBlockArea *>::iterator it = m_FullAreaList.begin(); it != m_FullAreaList.end(); ++it)
		{
			if (*it == pBlockOwner)
			{
				m_FullAreaList.erase(it);
				break;
			}
		}
		m_NonFullAreaList.push_back(pBlockOwner);
		m_nonFullAreasCount++;
	}
	pBlockOwner->FreeBlock(pExtent->GetNVMBlock());
}