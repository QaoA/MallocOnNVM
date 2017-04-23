#include "CLLogItem.h"
#include "CLLogArea.h"
#include <cassert>

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

CLLogItem::CLLogItem(void * pAddress, unsigned long size, char * value):
m_address(pAddress),
m_size(size)
{
	assert(size <= sizeof(unsigned long));
	memcpy(m_address, value, size);
}

CLLogItem::~CLLogItem()
{
	if ((unsigned long)m_address & 0x1)
	{
		delete[](char *)m_pValue;
	}
}

bool CLLogItem::WriteLog(CLLogArea * pLogArea)
{
	assert(pLogArea);
	unsigned long logSize = m_size + sizeof(void *) + sizeof(unsigned long);
	unsigned long pLogWriteStartAddress = pLogArea->TryGetAndIncreaseCurrentWriteAddress(logSize);
	if (pLogWriteStartAddress == 0)
	{
		return false;
	}
	
	*(void **)(pLogWriteStartAddress) = GetAddress();
	pLogWriteStartAddress += sizeof(void *);
	*(unsigned long *)(pLogWriteStartAddress) = m_size;
	pLogWriteStartAddress += sizeof(unsigned long);
	if (m_size <= sizeof(void *))
	{
		memcpy((void *)pLogWriteStartAddress, m_value, m_size);
	}
	else
	{
		memcpy((void *)pLogWriteStartAddress, m_pValue, m_size);
	}
	return true;
}

void CLLogItem::SetValues()
{
	if (m_size <= sizeof(void *))
	{
		memcpy((void *)m_address, m_value, m_size);
	}
	else
	{
		memcpy((void *)GetAddress(), m_pValue, m_size);
	}
}

void CLLogItem::Recovery(unsigned long logStartAddress)
{	
	do 
	{
		void * pAddress = *(void **)logStartAddress;
		if (!pAddress)
		{
			break;
		}
		logStartAddress += sizeof(void *);
		unsigned long size = *(unsigned long *)(logStartAddress);
		logStartAddress += sizeof(unsigned long);
		memcpy(pAddress, (void *)logStartAddress, size);
	} while (true);
}

NS_END