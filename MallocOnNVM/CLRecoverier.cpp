#include "CLRecoverier.h"
#include <cassert>

CLRecoverier::CLRecoverier()
{
}

CLRecoverier::~CLRecoverier()
{
}

void CLRecoverier::DoRecovery()
{	
	//恢复NVMBlockArea
	//恢复Arena的数据结构
	//扫描所有的NVMBlockArea
	
}

void CLRecoverier::AddAllocatedMemoryInfo(SLNVMBlock * pNVMBlock, CLBlockArea * pBlockArea)
{
	assert(pNVMBlock && pBlockArea);
	m_collector.AddUsedMemory(pNVMBlock, pBlockArea);
}