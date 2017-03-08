#ifndef __NVM_MEMORY_USE_TABLE_H__
#define __NVM_MEMORY_USE_TABLE_H__

#include <set>
#include "CLExtent.h"

class CLExtent;

class CLNVMMemoryUseInfoCollector
{
public:
	struct SLCompare
	{
		bool operator()(CLExtent * pFirst, CLExtent * pSecond);
	};
public:
	CLNVMMemoryUseInfoCollector();
	~CLNVMMemoryUseInfoCollector();

public:
	void AddUsedMemory(SLNVMBlock * pNVMBlock, CLBlockArea * pBlockArea);

private:
	std::set<CLExtent *,SLCompare> m_set;
};

#endif