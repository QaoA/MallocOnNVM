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
	//�ָ�NVMBlockArea
	//�ָ�Arena�����ݽṹ
	//ɨ�����е�NVMBlockArea
	
}

void CLRecoverier::AddAllocatedMemoryInfo(SLNVMBlock * pNVMBlock, CLBlockArea * pBlockArea)
{
	assert(pNVMBlock && pBlockArea);
	m_collector.AddUsedMemory(pNVMBlock, pBlockArea);
}