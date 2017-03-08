#include "CLNVMMemoryUseInfoCollector.h"
#include <cassert>

using namespace std;

bool CLNVMMemoryUseInfoCollector::SLCompare::operator()(CLExtent * pFirst, CLExtent * pSecond)
{
	return   pFirst->GetNVMAddress() < pSecond->GetNVMAddress();
}

CLNVMMemoryUseInfoCollector::CLNVMMemoryUseInfoCollector()
{
}

CLNVMMemoryUseInfoCollector::~CLNVMMemoryUseInfoCollector()
{
}

void CLNVMMemoryUseInfoCollector::AddUsedMemory(SLNVMBlock * pNVMBlock, CLBlockArea * pBlockArea)
{
	CLExtent * pExtent = new CLExtent();
	pExtent->Recovery(pNVMBlock,pBlockArea);
	m_set.insert(pExtent);
}