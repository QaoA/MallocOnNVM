#ifndef __RECOVERIER_INFO_PACK_H__
#define __RECOVERIER_INFO_PACK_H__

#include<list>
#include <cstddef>

struct SLMemoryUseInfo;

class CLRecoveryInfoPack
{
public:
	CLRecoveryInfoPack();
	~CLRecoveryInfoPack();

public:
	bool AppendInfo(SLMemoryUseInfo * pInfo);

private:
	std::list<SLMemoryUseInfo *> m_infoList;
	void * m_pBaseAddress;
	size_t m_size;
};

#endif