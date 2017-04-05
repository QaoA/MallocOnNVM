#ifndef __LOG_ITEM_H__
#define __LOG_ITEM_H__

#include <cstring>

class CLLogArea;

template<int N>
class CLLogItem
{
	friend class CLLogArea;
public:
	CLLogItem(void * pAddress, void * value);
	~CLLogItem();

private:
	void * m_address;
	char m_values[N];
};

template<int N>
CLLogItem<N>::CLLogItem(void * pAddress, void * value) :
	m_address(pAddress)
{
	memcpy(&m_values, value, N);
}

template<int N>
CLLogItem<N>::~CLLogItem()
{
}

#endif