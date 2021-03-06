#include "CLExtentList.h"
#include <cassert>

NS_BEGIN
CLExtentList::CLExtentList():
m_extentCount(0),
m_extents()
{
}

CLExtentList::~CLExtentList()
{
}

unsigned int CLExtentList::GetExtentCount()
{
	return m_extentCount;
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

NS_END