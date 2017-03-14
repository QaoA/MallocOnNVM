#include "CLRecoverier.h"
#include "SLNVMBlockArea.h"
#include "CLGlobalBlockAreaManager.h"
#include "CLArenaManager.h"
#include "CLArena.h"
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
	CLGlobalBlockAreaManager::GetInstance()->Recovery(*this);
	int i = 0;
}

void CLRecoverier::AppendInfo(SLNVMBlockArea * pArea)
{
	m_collector.AppendAreaUseInfo(pArea, sizeof(SLNVMBlockArea));
}

void CLRecoverier::AppendInfo(SLNVMBlock * pBlock)
{
	m_collector.AppendMemoryUseInfo(pBlock, pBlock->m_size, pBlock->m_arenaId);
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