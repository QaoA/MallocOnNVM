#include "CLLogAreaManager.h"
#include "SLNVMLogAreaPointers.h"
#include "CLCriticalSection.h"
#include "CLNVMMemoryMapManager.h"
#include "CLLogArea.h"
#include "CLRecoverier.h"
#include <cassert>
#include <cstring>

using namespace std;

NS_BEGIN

CLLogAreaManager::CLLogAreaManager(SLNVMLogAreaPointers * pNVMLogAreaPointers):
m_pNVMLogAreaPointers(pNVMLogAreaPointers),
m_sem(SLNVMLogAreaPointers::GetMaxAreaPointerCount())
{
	assert(pNVMLogAreaPointers);
	int maxPointerCount = SLNVMLogAreaPointers::GetMaxAreaPointerCount();
	for (int i = 0; i < maxPointerCount; ++i)
	{
		m_freeLogAreaArray.push_back(i);
	}
}

CLLogAreaManager::~CLLogAreaManager()
{
}

void CLLogAreaManager::Recovery(CLRecoverier & recoverier)
{
	int maxPointerCount = SLNVMLogAreaPointers::GetMaxAreaPointerCount();
	for (int i = 0; i < maxPointerCount; ++i)
	{
		void * pCurrentArea = m_pNVMLogAreaPointers->m_logAreaArray[i];
		if (pCurrentArea != nullptr)
		{
			CLLogArea::Recovery(pCurrentArea);
			recoverier.AppendInfo(pCurrentArea, CLLogArea::GetLogAreaSize());
		}
	}
}

CLLogArea * CLLogAreaManager::GetArea()
{
	int index = 0;
	void * pCurrentArea = nullptr;
	m_sem.Wait();
	{
		CLCriticalSection cs(&m_lock);
		index = m_freeLogAreaArray.front();
		pCurrentArea = m_pNVMLogAreaPointers->m_logAreaArray[index];
		if (pCurrentArea == nullptr)
		{
			pCurrentArea = CLNVMMemoryMapManager::GetInstance()->MapMemory(CLLogArea::GetLogAreaSize());
			assert(pCurrentArea);
			m_pNVMLogAreaPointers->m_logAreaArray[index] = pCurrentArea;
		}
		m_freeLogAreaArray.pop_front();
	}
	return new CLLogArea(index, pCurrentArea, CLLogArea::GetLogAreaSize());
}

void CLLogAreaManager::FreeArea(CLLogArea * pLogArea)
{
	assert(pLogArea);
	{
		CLCriticalSection cs(&m_lock);
		m_freeLogAreaArray.push_back(pLogArea->GetIndex());
	}
	m_sem.Post();
	delete pLogArea;
}

NS_END