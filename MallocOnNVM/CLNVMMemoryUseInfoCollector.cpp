#include "CLNVMMemoryUseInfoCollector.h"
#include "SizeDefine.h"
#include "CLExtent.h"
#include "SLMemoryUseInfo.h"
#include <cassert>

using namespace std;

bool CLNVMMemoryUseInfoCollector::SLComparer::operator()(SLMemoryUseInfo * pFirst, SLMemoryUseInfo * pSecond)
{
	return (pFirst->m_pAddress) < (pSecond->m_pAddress);
}

CLNVMMemoryUseInfoCollector::CLNVMMemoryUseInfoCollector()
{
}

CLNVMMemoryUseInfoCollector::~CLNVMMemoryUseInfoCollector()
{
	for (set<SLMemoryUseInfo*>::iterator it = m_set.begin(); it != m_set.end(); ++it)
	{
		delete *it;
	}
	m_set.clear();
}

void CLNVMMemoryUseInfoCollector::AppendMemoryUseInfo(void * pAddress, size_t size, int arenaId)
{
	SLMemoryUseInfo * pInfo = new SLMemoryUseInfo;
	pInfo->m_pAddress = pAddress;
	pInfo->m_size = size;
	pInfo->m_arenaId = arenaId;
	pInfo->m_bIsBlockArea = false;
	set<SLMemoryUseInfo*>::iterator it = m_set.insert(pInfo).first;
}

void CLNVMMemoryUseInfoCollector::AppendAreaUseInfo(void * pAddress, size_t size)
{
	SLMemoryUseInfo * pInfo = new SLMemoryUseInfo;
	pInfo->m_pAddress = pAddress;
	pInfo->m_size = size;
	pInfo->m_arenaId = -1;
	pInfo->m_bIsBlockArea = true;
	set<SLMemoryUseInfo*>::iterator it = m_set.insert(pInfo).first;
}
