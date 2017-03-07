#include "CLGlobalBlockAreaManager.h"
#include "CLBlockArea.h"
#include "CLNVMMemoryMapManager.h"
#include "SLNVMBlockArea.h"
#include "CLCriticalSection.h"
#include <cassert>


CLGlobalBlockAreaManager::CLGlobalBlockAreaManager():
m_pFirstBlockArea(nullptr)
{
}

CLGlobalBlockAreaManager::~CLGlobalBlockAreaManager()
{
}

CLGlobalBlockAreaManager * CLGlobalBlockAreaManager::GetInstance()
{
	static CLGlobalBlockAreaManager instance;
	return &instance;
}

CLBlockArea * CLGlobalBlockAreaManager::AppendNewBlockArea()
{
	CLBlockArea * pBlockArea = InitABlockArea();
	pBlockArea->LinkToList(m_pFirstBlockArea);
	return pBlockArea;
}

CLBlockArea * CLGlobalBlockAreaManager::InitABlockArea()
{
	SLNVMBlockArea * pNVMBlockArea = (SLNVMBlockArea *)CLNVMMemoryMapManager::GetInstance()->MapMemory(SLNVMBlockArea::GetClassSize());
	CLBlockArea * pBlockArea = new CLBlockArea();
	pBlockArea->Format(pNVMBlockArea, m_pFirstBlockArea);
	return pBlockArea;
}

CLBlockArea * CLGlobalBlockAreaManager::GetABlockArea()
{
	CLCriticalSection cs(&m_lock);
	if (m_pFirstBlockArea == nullptr)
	{
		m_pFirstBlockArea = AppendNewBlockArea();
		return m_pFirstBlockArea;
	}
	else
	{
		CLBlockArea * pBlockArea = AppendNewBlockArea();
		return pBlockArea;
	}
}

void CLGlobalBlockAreaManager::DoRecovery()
{
	CLCriticalSection cs(&m_lock);
}