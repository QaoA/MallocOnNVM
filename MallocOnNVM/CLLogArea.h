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
	inline void SetLogAreaDataInvalid();
	inline void SetLogAreaDataValid();

public:
	bool WriteLog(CLLogItem & item);
	bool WriteLog(void * pAddress, unsigned int size, void * value);

public:
	static void Recovery(void * pLogArea);

private:
	inline bool CanWrite(unsigned int valueSize);

private:
	int m_index;
	bool m_writeFlag;
	void * m_pStartAddress;
	unsigned long m_pCurrentWriteAddress;
};

inline int CLLogArea::GetIndex()
{
	return m_index;
}

inline void CLLogArea::SetLogAreaDataInvalid()
{
	*(unsigned long *)(m_pStartAddress) = 0;
	m_writeFlag = true;
}

inline void CLLogArea::SetLogAreaDataValid()
{
	*(unsigned long *)(m_pStartAddress) = (~0);
	m_writeFlag = false;
}

inline bool CLLogArea::CanWrite(unsigned int valueSize)
{
	unsigned int writtedSize = reinterpret_cast<unsigned long>(m_pCurrentWriteAddress) - reinterpret_cast<unsigned long>(m_pStartAddress);
	if ((valueSize + writtedSize) > LOG_AREA_SIZE)
	{
		return false;
	}
	return true;
}

inline bool CLLogArea::WriteLog(CLLogItem & item)
{
	return WriteLog(item.GetAddress(), item.GetSize(), item.GetValueAddress());
}

NS_END
#endif