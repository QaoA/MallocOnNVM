#include "CLCriticalSection.h"

NS_BEGIN

CLCriticalSection::CLCriticalSection(ILLock * pLock):
m_pLock(pLock)
{
	m_pLock->Lock();
}


CLCriticalSection::~CLCriticalSection()
{
	m_pLock->Unlock();
}

NS_END