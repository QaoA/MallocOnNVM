#include "CLLogItem.h"

NS_BEGIN

CLLogItem::CLLogItem(void * pAddress, unsigned long size, void * value, bool deleteValue):
m_address(pAddress),
m_size(size),
m_pValue(value)
{
	if (deleteValue)
	{
		m_address = (void *)((unsigned long)m_address | 0x1);
	}
}

CLLogItem::~CLLogItem()
{
	if ((unsigned long)m_address & 0x1)
	{
		delete[](char *)m_pValue;
	}
}

NS_END