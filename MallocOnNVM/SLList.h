#ifndef __LIST_H__
#define __LIST_H__

#include"MacroDefine.h"

struct SLList
{
public:
	SLList();
	~SLList();

public:
	void Init();
	void Append(SLList * pPrevious);
	void Remove();

public:
	SLList * m_pPrevious;
	SLList * m_pNext;
};

#endif