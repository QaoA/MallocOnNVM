#ifndef __LOG_ITEM_H__
#define __LOG_ITEM_H__

#include "NVMMallocNameSpace.h"
#include <stdint.h>
#include <cstring>

NS_BEGIN

class CLLogArea;

class CLLogItem
{
public:
	CLLogItem(void * pAddress, unsigned long size, void * value, bool deleteValue = false);
	CLLogItem(void * pAddress, uint64_t value);
	CLLogItem(void * pAddress, uint32_t value);
	CLLogItem(void * pAddress, uint16_t value);
	CLLogItem(void * pAddress, uint8_t value);
	~CLLogItem();

public:
	bool WriteLog(CLLogArea * pLogArea);
	void SetValues();
	static void Recovery(unsigned long logStartAddress);

private:
	inline void * GetAddress();

private:
	void * m_address;
	unsigned long m_size;
	union
	{
		void * m_pValue;
		uint64_t m_u64Value;
		uint32_t m_u32Value;
		uint16_t m_u16Value;
		uint8_t m_u8Value;
	};
};

inline void * CLLogItem::GetAddress()
{
	return (void *)((unsigned long)m_address & (~0x1));
}

NS_END
#endif