#ifndef __LOG_ITEM_H__
#define __LOG_ITEM_H__

#include "NVMMallocNameSpace.h"
#include <cstring>

NS_BEGIN

class CLLogArea;

class CLLogItem
{
public:
	CLLogItem(void * pAddress, unsigned long size, void * value, bool deleteValue = false);
	CLLogItem(void * pAddress, unsigned long size, char * pValue);
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
		char m_value[sizeof(void *)];
	};
};

inline void * CLLogItem::GetAddress()
{
	return (void *)((unsigned long)m_address & (~0x1));
}

NS_END
#endif