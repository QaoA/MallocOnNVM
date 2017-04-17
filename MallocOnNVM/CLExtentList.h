#ifndef __EXTENT_LIST_H__
#define __EXTENT_LIST_H__

#include "NVMMallocNameSpace.h"
#include <set>

NS_BEGIN

class CLExtent;

class CLExtentList
{
public:
	CLExtentList();
	~CLExtentList();

public:
	unsigned int GetExtentCount();
	CLExtent * GetExtent();
	void PutExtent(CLExtent * pExtent);
	void RemoveExtent(CLExtent * pExtent);

private:
	unsigned int m_extentCount;
	std::set<CLExtent *> m_extents;
};

NS_END
#endif