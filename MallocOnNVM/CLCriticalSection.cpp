#include "CLCriticalSection.h"

CLCriticalSection::CLCriticalSection(ILLock * pLock):
m_pLock(pLock)
{
	m_pLock->Lock();
}


CLCriticalSection::~CLCriticalSection()
{
	m_pLock->Unlock();
}
