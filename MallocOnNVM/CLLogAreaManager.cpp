#include "CLLogAreaManager.h"
#include "SLNVMLogAreaPointers.h"
#include "CLCriticalSection.h"
#include "CLNVMMemoryMapManager.h"
#include "CLLogArea.h"
#include "CLRecoverier.h"
#include <cassert>
#include <cstring>

using namespace std;

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

void CLLogAreaManager::Recovery(LogRecoveryFunc recoveryFunc, CLRecoverier & recoverier)
{
	assert(recoveryFunc);
	int maxPointerCount = SLNVMLogAreaPointers::GetMaxAreaPointerCount();
	for (int i = 0; i < maxPointerCount; ++i)
	{
		void * pCurrentArea = m_pNVMLogAreaPointers->m_logAreaArray[i];
		if (pCurrentArea != nullptr)
		{
			CLLogArea tmp(i, pCurrentArea, LOG_AREA_SIZE);
			recoveryFunc(tmp);
			recoverier.AppendInfo(pCurrentArea, LOG_AREA_SIZE);
		}
	}
}

CLLogArea * CLLogAreaManager::GetArea()
{
	m_sem.Wait();
	{
		CLCriticalSection cs(&m_lock);
		int index = m_freeLogAreaArray.front();
		void * pCurrentArea = m_pNVMLogAreaPointers->m_logAreaArray[index];
		if (pCurrentArea == nullptr)
		{
			pCurrentArea = CLNVMMemoryMapManager::GetInstance()->MapMemory(LOG_AREA_SIZE);
			assert(pCurrentArea);
			m_pNVMLogAreaPointers->m_logAreaArray[index] = pCurrentArea;
		}
		m_freeLogAreaArray.pop_front();
		return new CLLogArea(index, pCurrentArea, LOG_AREA_SIZE);
	}
}

void CLLogAreaManager::FreeArea(CLLogArea & pLogArea)
{
	{
		CLCriticalSection cs(&m_lock);
		m_freeLogAreaArray.push_back(pLogArea.GetIndex());
	}
	m_sem.Post();
}
