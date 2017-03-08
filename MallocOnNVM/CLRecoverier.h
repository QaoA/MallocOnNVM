#ifndef __RECOVERIER_H__
#define __RECOVERIER_H__

#include "CLNVMMemoryUseInfoCollector.h"

class CLRecoverier
{
public:
	CLRecoverier();
	~CLRecoverier();

public:
	void DoRecovery();
	void AddAllocatedMemoryInfo(SLNVMBlock * pNVMBlock, CLBlockArea * pBlockArea);

private:
	CLNVMMemoryUseInfoCollector m_collector;
};

#endif