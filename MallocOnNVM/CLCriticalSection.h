#ifndef __CRITICAL_SECTION_H__
#define __CRITICAL_SECTION_H__

#include "ILLock.h"

class CLCriticalSection
{
public:
	CLCriticalSection(ILLock * pLock);
	~CLCriticalSection();

private:
	ILLock * m_pLock;
};

#endif