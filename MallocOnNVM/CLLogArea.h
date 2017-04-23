#ifndef __LOG_AREA_H__
#define __LOG_AREA_H__

#include "SizeDefine.h"
#include "CLLogItem.h"
#include "NVMMallocNameSpace.h"
#include <cstring>

NS_BEGIN

#define LOG_AREA_SIZE PAGE_SIZE

class CLLogArea
{
public:
	CLLogArea(int index, void * pNVMAddress, unsigned int size);
	~CLLogArea();

public:
	inline int GetIndex();
	inline void WriteLogStart();
	inline void WriteLog(CLLogItem & logItem);
	inline void WriteLog(void * pAddress, unsigned long size, void * pValue);
	inline void WriteLogEnd();

public:
	unsigned long TryGetAndIncreaseCurrentWriteAddress(unsigned long writeLogSize);

public:
	static void Recovery(void * pLogArea);

private:
	int m_index;
	void * m_pStartAddress;
	unsigned long m_pCurrentWriteAddress;
};

inline int CLLogArea::GetIndex()
{
	return m_index;
}

inline void CLLogArea::WriteLogStart()
{
	*(unsigned long *)m_pStartAddress = 0;
}

inline void CLLogArea::WriteLog(CLLogItem & logItem)
{
	logItem.WriteLog(this);
}

inline void CLLogArea::WriteLog(void * pAddress, unsigned long size, void * pValue)
{
	CLLogItem item(pAddress, size, pValue);
	item.WriteLog(this);
}

inline void CLLogArea::WriteLogEnd()
{
	*(unsigned long *)m_pCurrentWriteAddress = 0;
	*(unsigned long *)m_pStartAddress = (~0);
}

NS_END
#endif