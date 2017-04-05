#include "CLRecoverier.h"
#include "SLNVMBlockArea.h"
#include "CLGlobalBlockAreaManager.h"
#include "CLArenaManager.h"
#include "CLArena.h"
#include "CLNVMMemoryMapManager.h"
#include "SLMemoryUseInfo.h"
#include "CLAllocatedExtentManager.h"
#include "CLBaseMetadata.h"
#include <cassert>

using namespace std;

CLRecoverier::CLRecoverier()
{
}

CLRecoverier::~CLRecoverier()
{
}

void CLRecoverier::DoRecovery()
{
	CLNVMMemoryMapManager::GetInstance()->GetBaseMetadata()->Recovery(*this);
	CLGlobalBlockAreaManager::GetInstance()->Recovery(*this);
	DispatchAllMemoryInfo();
}

void CLRecoverier::DispatchBlockArea(CLBlockArea * pBlockArea, int arenaId)
{
	assert(pBlockArea);
	if (arenaId == -1)
	{
		CLGlobalBlockAreaManager::GetInstance()->RecieveFreeBlockAreaRecovery(pBlockArea);
	}
	else
	{
		CLArenaManager::GetInstance()->GetArenaRecovery(arenaId)->RecieveBlockAreaRecovery(pBlockArea);
	}
}

void CLRecoverier::DispatchAllMemoryInfo()
{
	SLMemoryUseInfo * pInfo = nullptr;
	m_collector.MakeUseInfoReady();
	CLNVMMemoryMapManager::GetInstance()->RecieveLastMapAddressRecovery(reinterpret_cast<void *>(m_collector.GetLastBoundary()));
	while ((pInfo = m_collector.GetUseInfoOneByOne()) != nullptr)
	{
		switch (pInfo->GetType())
		{
		case MEM_BLOCK:
			DispacthBlockInfo(pInfo);
			break;
		case MEM_AREA:
			DispatchAreaInfo(pInfo);
			break;
		case MEM_FREE:
			DispatchFreeInfo(pInfo);
			break;
		case MEM_RESERVE:
			break;
		default:
			break;
		}
		delete pInfo;
	}
}

void CLRecoverier::DispacthBlockInfo(SLMemoryUseInfo * pInfo)
{
	assert(pInfo && pInfo->GetType() == MEM_BLOCK);
	CLArenaManager::GetInstance()->GetArenaRecovery(pInfo->GetArenaId())->RecieveExtentRecovery(pInfo->m_pExtent);
	if (pInfo->m_pExtent->IsOccupied())
	{
		CLAllocatedExtentManager::GetInstance()->Put(pInfo->m_pExtent);
	}
}

void CLRecoverier::DispatchAreaInfo(SLMemoryUseInfo * pInfo)
{
	assert(pInfo && pInfo->GetType() == MEM_AREA);
	CLBlockArea * pArea = pInfo->m_pBlockArea;
	if (pArea->IsEmpty())
	{
		CLGlobalBlockAreaManager::GetInstance()->RecieveFreeBlockAreaRecovery(pArea);
	}
	else
	{
		CLArenaManager::GetInstance()->GetArena(pInfo->GetArenaId())->RecieveBlockAreaRecovery(pArea);
	}
}

void CLRecoverier::DispatchFreeInfo(SLMemoryUseInfo * pInfo)
{
	assert(pInfo && pInfo->GetType() == MEM_FREE);
	CLNVMMemoryMapManager::GetInstance()->RecieveFreePages(pInfo->m_pFreePage->m_pAddress, pInfo->m_pFreePage->m_size);
	delete pInfo->m_pFreePage;
}