#include "SLList.h"

SLList::SLList() :
m_pPrevious(this),
m_pNext(this)
{
}

SLList::~SLList()
{
}

void SLList::Append(SLList * pPrevious)
{
	m_pPrevious = pPrevious;
	m_pNext = pPrevious->m_pNext;
	m_pPrevious->m_pNext = this;
	m_pNext->m_pPrevious = this;
}

void SLList::Remove()
{
	m_pPrevious->m_pNext = m_pNext;
	m_pNext->m_pPrevious = m_pPrevious;
}
