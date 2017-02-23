#ifndef __LIST_H__
#define __LIST_H__

struct SLList
{
public:
	SLList();
	~SLList();

public:
	void InitDefault();
	void InitWithKnownNode(SLList * pPrevious);
	void LinkToList(SLList * pPrevious);
	void Remove();

public:
	SLList * m_pPrevious;
	SLList * m_pNext;
};

#endif