#ifndef __PAGE_MANAGER_H__
#define __PAGE_MANAGER_H__

#include <map>

class CLPageManager
{
public:
	CLPageManager();
	~CLPageManager();

public:
	void * GetPages(unsigned int expectedPageCount);
	void PutPages(void * pAddress, unsigned int pageCount);

private:
	void * CalculateAddress(void * pBaseAddress, unsigned int pageCount);
	bool CanMerge(void * pBaseAddress, unsigned int pageCount, void * pAnotherAddress);

private:
	std::map<void *, unsigned int> m_pagesMap;
};

#endif
