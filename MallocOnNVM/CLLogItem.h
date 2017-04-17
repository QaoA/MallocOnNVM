#ifndef __LOG_ITEM_H__
#define __LOG_ITEM_H__

#include <cstring>

class CLLogArea;

class CLLogItem
{
public:
	CLLogItem(void * pAddress, unsigned long size, void * value, bool deleteValue = false);
	~CLLogItem();

public:
	inline void * GetAddress();
	inline unsigned long GetSize();
	inline void * GetValueAddress();

private:
	void * m_address;
	unsigned long m_size;
	void * m_pValue;
};

inline void * CLLogItem::GetAddress()
{
	return (void *)((unsigned long)m_address & 0x1);
}

inline unsigned long CLLogItem::GetSize()
{
	return m_size;
}

inline void * CLLogItem::GetValueAddress()
{
	return m_pValue;
}

#endif