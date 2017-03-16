#include "CLGlobalBlockAreaManager.h"
#include "CLBlockArea.h"
#include "CLNVMMemoryMapManager.h"
#include "CLCriticalSection.h"
#include "CLBaseMetadata.h"
#include "CLRecoverier.h"
#include <cassert>

using namespace std;

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

CLBlockArea * CLGlobalBlockAreaManager::GetABlockArea()
{
	CLCriticalSection cs(&m_lock);
	if (!m_areaList.empty())
	{
		CLBlockArea * pReturnArea = m_areaList.front();
		m_areaList.pop_front();
		return pReturnArea;
	}
	SLNVMBlockArea * pNVMBlockArea = (SLNVMBlockArea *)CLNVMMemoryMapManager::GetInstance()->MapMemory(CLBlockArea::GetClassSize());
	if (pNVMBlockArea == nullptr)
	{
		return nullptr;
	}
	CLBlockArea * pBlockArea = new CLBlockArea(pNVMBlockArea);
	pBlockArea->Format(m_pFirstBlockArea);
	if (m_pFirstBlockArea == nullptr)
	{
		m_pFirstBlockArea = pBlockArea;
		CLNVMMemoryMapManager::GetInstance()->GetBaseMetadata()->SetFirstBlockArea(pNVMBlockArea);
	}
	return pBlockArea;
}

void CLGlobalBlockAreaManager::FreeBlockArea(CLBlockArea * pArea)
{
	assert(pArea);
	CLCriticalSection cs(&m_lock);
	m_areaList.push_back(pArea);
}

void CLGlobalBlockAreaManager::FreeBlockAreas(list<CLBlockArea *> & areaList, unsigned int freeCount)
{
	CLCriticalSection cs(&m_lock);
	for (int i = 0; i < freeCount; ++i)
	{
		assert(!areaList.empty());
		m_areaList.push_back(areaList.front());
		areaList.pop_front();
	}
}

void CLGlobalBlockAreaManager::Recovery(CLRecoverier & recoverier)
{
	SLNVMBlockArea * pFirstNVMArea = CLNVMMemoryMapManager::GetInstance()->GetBaseMetadata()->GetFirstBlockArea();
	if (pFirstNVMArea == nullptr)
	{
		return;
	}
	m_pFirstBlockArea = new CLBlockArea(pFirstNVMArea);
	m_pFirstBlockArea->Recovery(recoverier);
	recoverier.AppendInfo(m_pFirstBlockArea);
	SLNVMBlockArea * pTmpNVMArea = pFirstNVMArea->GetNextBlockAreaRecovery();
	while (pTmpNVMArea != pFirstNVMArea)
	{
		CLBlockArea * pTmpArea = new CLBlockArea(pTmpNVMArea);
		pTmpArea->Recovery(recoverier);
		recoverier.AppendInfo(pTmpArea);
		pTmpNVMArea = pTmpNVMArea->GetNextBlockAreaRecovery();
	}
}

void CLGlobalBlockAreaManager::RecieveFreeBlockAreaRecovery(CLBlockArea * pBlockArea)
{
	assert(pBlockArea);
	m_areaList.push_back(pBlockArea);
}