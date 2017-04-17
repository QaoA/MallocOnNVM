#include "CLPageManager.h"
#include "SizeDefine.h"

NS_BEGIN

using namespace std;

CLPageManager::CLPageManager()
{
}

CLPageManager::~CLPageManager()
{
}

void * CLPageManager::GetPages(unsigned int expectedPageCount)
{
	void * pAddress = nullptr;
	for (map<void *, unsigned int>::iterator it = m_pagesMap.begin(); it != m_pagesMap.end(); ++it)
	{
		if ((*it).second == expectedPageCount)
		{
			pAddress = (*it).first;
			m_pagesMap.erase(it);
			return pAddress;
		}
		else if ((*it).second > expectedPageCount)
		{
			pAddress = (*it).first;
			unsigned int pageCount = (*it).second;
			it->second = pageCount - expectedPageCount;
			return CalculateAddress(pAddress, (*it).second);
		}
	}
	if (pAddress == nullptr)
	{
		return nullptr;
	}
}

void CLPageManager::PutPages(void * pAddress, unsigned int pageCount)
{
	if (m_pagesMap.empty())
	{
		m_pagesMap.insert(make_pair(pAddress, pageCount));
		return;
	}

	bool mergeArray[3] = { false, false, false };
	map<void *, unsigned int>::iterator it[3];
	unsigned int newPageCount = 0;
	it[1] = m_pagesMap.insert(make_pair(pAddress, pageCount)).first;
	if (it[1] != m_pagesMap.begin())
	{
		it[0] = it[1];
		it[0]--;
		if (CanMerge(it[0]->first, it[0]->second, it[1]->first))
		{
			newPageCount = it[0]->second + it[1]->second;
			mergeArray[0] = true; mergeArray[1] = true;
		}
	}
	it[2] = it[1];
	it[2]++;
	if (it[2] != m_pagesMap.end())
	{
		if (CanMerge(it[1]->first, it[1]->second, it[2]->first))
		{
			newPageCount += (newPageCount == 0 ? it[1]->second + it[2]->second : it[2]->second);
			mergeArray[1] = true; mergeArray[2] = true;
		}
	}
	bool modified = false;
	for (int i = 0; i < 3; ++i)
	{
		if (mergeArray[i])
		{
			if (!modified)
			{
				modified = true;
				it[i]->second = newPageCount;
			}
			else
			{
				m_pagesMap.erase(it[i]);
			}
		}
	}
}

void * CLPageManager::CalculateAddress(void * pBaseAddress, unsigned int pageCount)
{
	return reinterpret_cast<void *>(reinterpret_cast<unsigned long>(pBaseAddress)+pageCount*PAGE_SIZE);
}

bool CLPageManager::CanMerge(void * pBaseAddress, unsigned int pageCount, void * pAnotherAddress)
{
	return (reinterpret_cast<unsigned long>(pBaseAddress)+pageCount*PAGE_SIZE) == reinterpret_cast<unsigned long>(pAnotherAddress);
}

NS_END