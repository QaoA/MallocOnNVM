#ifndef __EXTENT_LIST_H__
#define __EXTENT_LIST_H__

#include <stack>

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

private:
	unsigned int m_extentCount;
	std::stack<CLExtent *> m_extents;
};

#endif