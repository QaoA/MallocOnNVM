#ifndef __NVM_MEMORY_USE_TABLE_H__
#define __NVM_MEMORY_USE_TABLE_H__

#include <set>
#include <cstddef>
#include <list>
#include "SizeDefine.h"

struct SLMemoryUseInfo;
struct SLNVMBlock;
class CLBlockArea;

class CLNVMMemoryUseInfoCollector
{
public:
	struct SLComparer
	{
		bool operator()(SLMemoryUseInfo * pFirst, SLMemoryUseInfo * pSecond);
	};

public:
	CLNVMMemoryUseInfoCollector();
	~CLNVMMemoryUseInfoCollector();

public:
	void AppendMemoryUseInfo(SLNVMBlock * pBlock, CLBlockArea * pOwner);
	void AppendAreaUseInfo(CLBlockArea * pArea);
	void AppendReservedAreaInfo(void * pReservedArea, unsigned int areaSize);
	SLMemoryUseInfo * GetUseInfoOneByOne();
	void MakeUseInfoReady();
	unsigned long GetLastBoundary();

private:
	void SetCurrentDatas();
	inline unsigned long GetStartBoundary(unsigned long pAddress);
	inline unsigned long GetEndBoundary(unsigned long pAddress);

private:
	std::set<SLMemoryUseInfo *, SLComparer> m_set;
	unsigned long m_currentStartAddress;
	unsigned long m_currentEndAddress;
	int m_currentArenaId;
};

unsigned long CLNVMMemoryUseInfoCollector::GetStartBoundary(unsigned long pAddress)
{
	return pAddress&(~PAGE_SIZE_MASK);
}

unsigned long CLNVMMemoryUseInfoCollector::GetEndBoundary(unsigned long pAddress)
{
	if (pAddress&PAGE_SIZE_MASK)
	{
		return (pAddress&(~PAGE_SIZE_MASK)) + PAGE_SIZE;
	}
	return pAddress;
}

#endif