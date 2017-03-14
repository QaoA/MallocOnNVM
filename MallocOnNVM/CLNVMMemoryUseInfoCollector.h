#ifndef __NVM_MEMORY_USE_TABLE_H__
#define __NVM_MEMORY_USE_TABLE_H__

#include <set>
#include <cstddef>
#include <list>

class CLExtent;
struct SLMemoryUseInfo;

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
	void AppendMemoryUseInfo(void * pAddress, size_t size, int arenaId);
	void AppendAreaUseInfo(void * pAddress, size_t size);

private:
	std::set<SLMemoryUseInfo *, SLComparer> m_set;
};

#endif