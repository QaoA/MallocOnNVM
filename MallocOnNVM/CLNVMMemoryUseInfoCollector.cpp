#include "CLNVMMemoryUseInfoCollector.h"
#include "SizeDefine.h"
#include "CLExtent.h"
#include "SLMemoryUseInfo.h"
#include "SLNVMBlockArea.h"
#include <cassert>

using namespace std;

bool CLNVMMemoryUseInfoCollector::SLComparer::operator()(SLMemoryUseInfo * pFirst, SLMemoryUseInfo * pSecond)
{
	return (pFirst->GetAddress()) < (pSecond->GetAddress());
}

CLNVMMemoryUseInfoCollector::CLNVMMemoryUseInfoCollector():
m_set(),
m_currentStartAddress(0),
m_currentEndAddress(0),
m_currentArenaId(0)
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

void CLNVMMemoryUseInfoCollector::AppendMemoryUseInfo(SLNVMBlock * pBlock, CLBlockArea * pOwner)
{
	assert(pBlock && pOwner);
	CLExtent * pExtent = new CLExtent();
	pExtent->Recovery(pBlock, pOwner);
	m_set.insert(new SLMemoryUseInfo(pExtent));
}

void CLNVMMemoryUseInfoCollector::AppendAreaUseInfo(CLBlockArea * pArea)
{
	assert(pArea);
	m_set.insert(new SLMemoryUseInfo(pArea));
}

void CLNVMMemoryUseInfoCollector::MakeUseInfoReady()
{
	if (!m_set.empty())
	{
		SLMemoryUseInfo * pFirstInfo = (*m_set.begin());
		m_currentStartAddress = GetStartBoundary(pFirstInfo->GetAddress());
		m_currentEndAddress = GetEndBoundary(pFirstInfo->GetEndAddress());
		m_currentArenaId = pFirstInfo->GetArenaId();
	}
}

SLMemoryUseInfo * CLNVMMemoryUseInfoCollector::GetUseInfoOneByOne()
{
	CLExtent * pExtent = nullptr;
	if (m_set.empty())
	{
		if (m_currentEndAddress != m_currentStartAddress)
		{
			assert(m_currentStartAddress < m_currentEndAddress);
			pExtent = new CLExtent();
			pExtent->Recovery(reinterpret_cast<void *>(m_currentStartAddress),m_currentEndAddress - m_currentStartAddress, m_currentArenaId);
			m_currentStartAddress = m_currentEndAddress;
			return new SLMemoryUseInfo(pExtent);
		}
		return nullptr;
	}
	if (m_currentStartAddress == m_currentEndAddress)
	{
		unsigned long firstInfoAddressBoundary = GetStartBoundary((*m_set.begin())->GetAddress());
		if (m_currentEndAddress == firstInfoAddressBoundary)
		{
			MakeUseInfoReady();
		}
		else
		{
			SLMemoryUseInfo * pReturnInfo = new SLMemoryUseInfo(reinterpret_cast<void *>(m_currentEndAddress), firstInfoAddressBoundary);
			MakeUseInfoReady();
			return pReturnInfo;
		}
	}
	SLMemoryUseInfo * pFirstInfo = *m_set.begin();
	if (pFirstInfo->GetAddress() == m_currentStartAddress)
	{
		m_set.erase(m_set.begin());
		m_currentStartAddress = pFirstInfo->GetEndAddress();
		return pFirstInfo;
	}
	else
	{
		assert(m_currentStartAddress < m_currentEndAddress);
		pExtent = new CLExtent();
		pExtent->Recovery(reinterpret_cast<void *>(m_currentStartAddress), m_currentEndAddress - m_currentStartAddress, m_currentArenaId);
		m_currentStartAddress = m_currentEndAddress;
		return new SLMemoryUseInfo(pExtent);
	}
}