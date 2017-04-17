#ifndef __NVM_LIST_H__
#define __NVM_LIST_H__

#include <cassert>
#include "MacroDefine.h"
#include "NVMMallocNameSpace.h"

NS_BEGIN

struct SLNVMList
{
public:
	inline void Init(SLNVMList * pPrevious = nullptr);
	inline void Append(SLNVMList * pPrevious);
	inline void Remove();

public:
	inline SLNVMList * GetNextRecovery();

public:
	SLNVMList * m_pPrevious;
	SLNVMList * m_pNext;
};

void SLNVMList::Init(SLNVMList * pPrevious)
{
	if (pPrevious)
	{
		m_pPrevious = pPrevious;
		m_pNext = pPrevious->m_pNext;
	}
	else
	{
		m_pPrevious = this;
		m_pNext = this;
	}

}

void SLNVMList::Append(SLNVMList * pPrevious)
{
	assert(pPrevious);
	m_pPrevious = pPrevious;
	m_pNext = pPrevious->m_pNext;

	SLNVMList * pNext = pPrevious->m_pNext;
	pNext->m_pPrevious = this;
	pPrevious->m_pNext = this;
}

void SLNVMList::Remove()
{
	SLNVMList * pPrevious = this->m_pPrevious;
	SLNVMList * pNext = this->m_pNext;
	pPrevious->m_pNext = pNext;
	pNext->m_pPrevious = pPrevious;
}

SLNVMList * SLNVMList::GetNextRecovery()
{
	SLNVMList * pNextsNext = m_pNext->m_pNext;
	SLNVMList * pLogicalSelf = pNextsNext->m_pPrevious->m_pPrevious;
	if (pLogicalSelf != this)
	{
		m_pNext = pLogicalSelf;
	}
	return m_pNext;
}

NS_END
#endif