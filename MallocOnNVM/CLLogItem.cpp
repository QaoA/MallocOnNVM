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

CLLogItem::CLLogItem(void * pAddress, uint64_t value):
m_address(pAddress),
m_size(sizeof(value)),
m_u64Value(value)
{
}

CLLogItem::CLLogItem(void * pAddress, uint32_t value):
m_address(pAddress),
m_size(sizeof(value)),
m_u32Value(value)
{
}

CLLogItem::CLLogItem(void * pAddress, uint16_t value):
m_address(pAddress),
m_size(sizeof(value)),
m_u16Value(value)
{
}

CLLogItem::CLLogItem(void * pAddress, uint8_t value):
m_address(pAddress),
m_size(sizeof(value)),
m_u8Value(value)
{
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
		switch (m_size)
		{
		case sizeof(uint64_t) :
			*(uint64_t *)pLogWriteStartAddress = m_u64Value;
			break;
		case sizeof(uint32_t) :
			*(uint32_t *)pLogWriteStartAddress = m_u32Value;
			break;
		case sizeof(uint16_t) :
			*(uint16_t *)pLogWriteStartAddress = m_u16Value;
			break;
		case sizeof(uint8_t) :
			*(uint8_t *)pLogWriteStartAddress = m_u8Value;
			break;
		default:
			break;
		}
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
		switch (m_size)
		{
		case sizeof(uint64_t) :
			*(uint64_t *)m_address = m_u64Value;
			break;
		case sizeof(uint32_t) :
			*(uint32_t *)m_address = m_u32Value;
			break;
		case sizeof(uint16_t) :
			*(uint16_t *)m_address = m_u16Value;
			break;
		case sizeof(uint8_t) :
			*(uint8_t *)m_address = m_u8Value;
			break;
		default:
			break;
		}
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
		logStartAddress += size;
	} while (true);
}

NS_END