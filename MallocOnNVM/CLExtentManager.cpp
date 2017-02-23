#include "CLExtentManager.h"
#include "CLExtent.h"
#include <cassert>

CLExtentManager::CLExtentManager():
m_extents(),
m_freeExtentCount(0)
{
}

CLExtentManager::~CLExtentManager()
{
	CLExtent * pExtent = nullptr;
	for (; m_freeExtentCount > 0; --m_freeExtentCount)
	{
		pExtent = m_extents.top();
		m_extents.pop();
		DeleteAExtent(pExtent);
	}
}

CLExtent * CLExtentManager::GetExtent()
{
	if (m_freeExtentCount == 0)
	{
		return NewAExtent();
	}
	CLExtent * pReturnExtent = m_extents.top();
	m_extents.pop();
	return pReturnExtent;
}

void CLExtentManager::FreeExtent(CLExtent * pExtent)
{
	assert(pExtent);
	if (m_freeExtentCount >= MAX_CACHE_EXTENT_COUNT)
	{
		unsigned int restCount = MAX_CACHE_EXTENT_COUNT >> REST_EXTENT_RATE_BIT;
		CLExtent * pTmpExtent = nullptr;
		for (; m_freeExtentCount > restCount; --m_freeExtentCount)
		{
			pTmpExtent = m_extents.top();
			m_extents.pop();
			DeleteAExtent(pTmpExtent);
		}
	}
	m_extents.push(pExtent);
	m_freeExtentCount++;
}

CLExtent * CLExtentManager::NewAExtent()
{
	return new CLExtent();
}

void CLExtentManager::DeleteAExtent(CLExtent * pExtent)
{
	delete pExtent;
}