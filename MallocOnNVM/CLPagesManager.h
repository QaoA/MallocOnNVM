#ifndef __PAGES_MANAGER_H__
#define __PAGES_MANAGER_H__

#include "SizeDefine.h"
#include <set>

struct SLPages
{
	void * m_pAddress;
	unsigned int m_pageCount;
	bool operator<(const SLPages &) const;
};

class CLPagesManager
{
public:
	CLPagesManager();
	~CLPagesManager();

public:
	void * GetPages(unsigned int pageCount);
	void PutPages(void * pAddress,unsigned int pageCount);

private:
	void * TryGetPagesFromLargePagesSet(unsigned int pageCount);
	void * TryGetPagesFromPagesArray(unsigned int pageCount);
	void AppendNewPages(SLPages & page);
	unsigned int PageCount2Index(unsigned int pageCount);

private:
	std::set<SLPages> m_pageSet[PAGES_ARRAY_SIZE];
	std::set<SLPages> m_largePagesSet;
};

#endif