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
	CLExtent * pExtent = m_extents.top();
	m_extents.pop();
	m_extentCount--;
	return pExtent;
}

void CLExtentList::PutExtent(CLExtent * pExtent)
{
	assert(pExtent);
	m_extents.push(pExtent);
	m_extentCount++;
}