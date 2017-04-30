#include "CLNameServerArea.h" 
#include "SLNVMNameServerArea.h"

NS_BEGIN

CLNameServerArea::CLNameServerArea(SLNVMNameServerArea * pArea):
m_address(pArea)
{
}

CLNameServerArea::~CLNameServerArea()
{
}

unsigned int CLNameServerArea::GetAreaSize()
{
	return sizeof(SLNVMNameServerArea);
}

NS_END