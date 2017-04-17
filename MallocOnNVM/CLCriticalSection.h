#ifndef __CRITICAL_SECTION_H__
#define __CRITICAL_SECTION_H__

#include "ILLock.h"
#include "NVMMallocNameSpace.h"

NS_BEGIN

class CLCriticalSection
{
public:
	CLCriticalSection(ILLock * pLock);
	~CLCriticalSection();

private:
	ILLock * m_pLock;
};

NS_END
#endif