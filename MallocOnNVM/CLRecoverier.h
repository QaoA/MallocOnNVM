#ifndef __RECOVERIER_H__
#define __RECOVERIER_H__

#include "CLNVMMemoryUseInfoCollector.h"
#include <list>

struct SLNVMBlock;
class CLBlockArea;

class CLRecoverier
{
public:
	CLRecoverier();
	~CLRecoverier();

public:
	void DoRecovery();
	void DispatchBlockArea(CLBlockArea * pBlockArea, int arenaId);

public:
	inline void AppendInfo(SLNVMBlock * pBlock, CLBlockArea * pOwner);
	inline void AppendInfo(CLBlockArea * pArea);
	inline void AppendInfo(void * pReserveredArea, unsigned int areaSize);

private:
	void DispatchAllMemoryInfo();
	void DispatchFreeInfo(SLMemoryUseInfo * pInfo);
	void DispacthBlockInfo(SLMemoryUseInfo * pInfo);
	void DispatchAreaInfo(SLMemoryUseInfo * pInfo);

private:
	CLNVMMemoryUseInfoCollector m_collector;
};

void CLRecoverier::AppendInfo(CLBlockArea * pArea)
{
	m_collector.AppendAreaUseInfo(pArea);
}

void CLRecoverier::AppendInfo(SLNVMBlock * pBlock, CLBlockArea * pOwner)
{
	m_collector.AppendMemoryUseInfo(pBlock, pOwner);
}

void CLRecoverier::AppendInfo(void * pReserveredArea, unsigned int areaSize)
{
	m_collector.AppendReservedAreaInfo(pReserveredArea, areaSize);
}

#endif