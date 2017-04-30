#ifndef __LOG_AREA_H__
#define __LOG_AREA_H__

#include "CLLogItem.h"
#include "NVMMallocNameSpace.h"
#include <cstring>

NS_BEGIN

class CLLogArea
{
public:
	CLLogArea(int index, void * pNVMAddress, unsigned int size);
	~CLLogArea();

public:
	inline int GetIndex();
	inline void WriteLogStart();
	inline void WriteLog(CLLogItem & item);
	inline void WriteLogEnd();

public:
	unsigned long TryGetAndIncreaseCurrentWriteAddress(unsigned long writeLogSize);

public:
	static void Recovery(void * pLogArea);
	static unsigned int GetLogAreaSize();

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

inline void CLLogArea::WriteLog(CLLogItem & item)
{
	item.WriteLog(this);
}

inline void CLLogArea::WriteLogEnd()
{
	*(unsigned long *)m_pCurrentWriteAddress = 0;
	*(unsigned long *)m_pStartAddress = (~0);
}

NS_END
#endif