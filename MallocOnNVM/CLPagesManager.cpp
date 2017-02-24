#include "CLPagesManager.h"
#include <cassert>

using namespace std;

bool SLPages::operator<(const SLPages & anotherPages) const
{
	return m_pAddress < anotherPages.m_pAddress;
}

CLPagesManager::CLPagesManager()
{
}

CLPagesManager::~CLPagesManager()
{
}

void * CLPagesManager::GetPages(unsigned int pageCount)
{
	if (pageCount > PAGES_MAX_PAGE_COUNT)
	{
		return TryGetPagesFromLargePagesSet(pageCount);
	}
	else
	{
		return TryGetPagesFromPagesArray(pageCount);
	}
}

void CLPagesManager::PutPages(void * pAddress,unsigned int pageCount)
{
	assert(pAddress && pageCount);
	SLPages tmpPage = { pAddress, pageCount };
	AppendNewPages(tmpPage);
}

void * CLPagesManager::TryGetPagesFromLargePagesSet(unsigned int pageCount)
{
	void * pReturnAddress = nullptr;
	for (set<SLPages>::iterator it = m_largePagesSet.begin(); it != m_largePagesSet.end(); ++it)
	{
		if ((*it).m_pageCount > pageCount)
		{
			SLPages tmpPage = (*it);
			m_largePagesSet.erase(it);
			pReturnAddress = reinterpret_cast<void *>(reinterpret_cast<unsigned long>(tmpPage.m_pAddress) + (tmpPage.m_pageCount - pageCount) * PAGE_SIZE);
			tmpPage.m_pageCount -= pageCount;
			AppendNewPages(tmpPage);
			return pReturnAddress;
		}
		else if ((*it).m_pageCount == pageCount)
		{
			pReturnAddress = (*it).m_pAddress;
			m_largePagesSet.erase(it);
			return pReturnAddress;
		}
	}
	return pReturnAddress;
}

void * CLPagesManager::TryGetPagesFromPagesArray(unsigned int pageCount)
{
	assert(pageCount <= PAGES_MAX_PAGE_COUNT);
	unsigned int index = PageCount2Index(pageCount);
	for (int i = index; i < PAGES_ARRAY_SIZE; ++i)
	{
		if (!m_pageSet[i].empty())
		{
			set<SLPages>::iterator it = m_pageSet[i].begin();
			SLPages tmpPages = *it;
			m_pageSet[i].erase(it);
			assert(tmpPages.m_pageCount >= pageCount);
			if (tmpPages.m_pageCount == pageCount)
			{
				return tmpPages.m_pAddress;
			}
			else
			{
				tmpPages.m_pageCount -= pageCount;
				void * pReturnAddress = reinterpret_cast<void *>(reinterpret_cast<unsigned long>(tmpPages.m_pAddress) + (tmpPages.m_pageCount - pageCount) * PAGE_SIZE);
				AppendNewPages(tmpPages);
				return pReturnAddress;
			}
		}
	}
	return nullptr;
}

void CLPagesManager::AppendNewPages(SLPages & page)
{
	if (page.m_pageCount > PAGES_MAX_PAGE_COUNT)
	{
		m_largePagesSet.insert(page);
		return;
	}
	unsigned int index = PageCount2Index(page.m_pageCount);
	m_pageSet[index].insert(page);
}

unsigned int CLPagesManager::PageCount2Index(unsigned int pageCount)
{
	return pageCount - 1;
}