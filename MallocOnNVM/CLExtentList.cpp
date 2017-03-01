#include "CLExtentList.h"
#include <cassert>

CLExtentList::CLExtentList():
m_extentCount(0),
m_extents()
{
}

CLExtentList::~CLExtentList()
{
}

CLExtent * CLExtentList::GetExtent()
{
	if (m_extentCount == 0)
	{
		return nullptr;
	}
	CLExtent * pExtent = *m_extents.begin();
	m_extents.erase(m_extents.begin());
	m_extentCount--;
	return pExtent;
}

void CLExtentList::PutExtent(CLExtent * pExtent)
{
	assert(pExtent);
	m_extents.insert(pExtent);
	m_extentCount++;
}

void CLExtentList::RemoveExtent(CLExtent * pExtent)
{
	m_extents.erase(pExtent);
	m_extentCount--;
}