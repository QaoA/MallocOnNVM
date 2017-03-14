#ifndef __RECOVERIER_H__
#define __RECOVERIER_H__

#include "CLNVMMemoryUseInfoCollector.h"
#include <list>

struct SLNVMBlock;
struct SLNVMBlockArea;
class CLBlockArea;

class CLRecoverier
{
public:
	CLRecoverier();
	~CLRecoverier();

public:
	void DoRecovery();
	void AppendInfo(SLNVMBlock * pBlock);
	void AppendInfo(SLNVMBlockArea * pArea);
	void DispatchBlockArea(CLBlockArea * pBlockArea, int arenaId);

private:
	CLNVMMemoryUseInfoCollector m_collector;
};

#endif