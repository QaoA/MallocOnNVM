#include "SLList.h"
#include <cstring>
#include <cassert>

SLList::SLList()
{
	InitDefault();
}

SLList::~SLList()
{
}

void SLList::InitDefault()
{
	m_pPrevious = this;
	m_pNext = this;
}

void SLList::InitWithKnownNode(SLList * pPrevious)
{
	assert(pPrevious);
	m_pPrevious = pPrevious;
	m_pNext = pPrevious->m_pNext;
}

void SLList::LinkToList(SLList * pPrevious)
{
	assert(pPrevious);
	SLList * pNext = pPrevious->m_pNext;

	pNext->m_pPrevious = this;
	pPrevious->m_pNext = this;
}

void SLList::AppendToList(SLList * pPrevious)
{
	InitWithKnownNode(pPrevious);
	LinkToList(m_pPrevious);
}

void SLList::Remove()
{
	SLList * pPrevious = this->m_pPrevious;
	SLList * pNext = this->m_pNext;
	pPrevious->m_pNext = pNext;
	pNext->m_pPrevious = pPrevious;
}

SLList * SLList::GetNext()
{
	return m_pNext;
}

SLList * SLList::GetPrevious()
{
	return m_pPrevious;
}