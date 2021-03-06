#include "SLMemoryUseInfo.h"

NS_BEGIN

SLFreeInfo::SLFreeInfo(void * pAddress, unsigned int size):
m_pAddress(pAddress),
m_size(size)
{
}

SLMemoryUseInfo::SLMemoryUseInfo(CLExtent * pExtent) :
m_pExtent(pExtent),
m_type(MEM_BLOCK)
{
}

SLMemoryUseInfo::SLMemoryUseInfo(CLBlockArea * pArea) :
m_pBlockArea(pArea),
m_type(MEM_AREA)
{
}

SLMemoryUseInfo::SLMemoryUseInfo(void * pAddress, unsigned int size) :
m_pFreePage(new SLFreeInfo(pAddress, size)),
m_type(MEM_FREE)
{
}

SLMemoryUseInfo::SLMemoryUseInfo(void * pReservedArea, unsigned int areaSize, bool reserveFlag):
m_pFreePage(new SLReservedArea(pReservedArea,areaSize)),
m_type(MEM_RESERVE)
{
}

NS_END