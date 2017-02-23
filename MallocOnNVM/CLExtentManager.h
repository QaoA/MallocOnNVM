#ifndef __EXTENT_MANAGER_H__
#define __EXTENT_MANAGER_H__

#include <stack>

class CLExtent;

class CLExtentManager
{
public:
	CLExtentManager();
	~CLExtentManager();

public:
	CLExtent * GetExtent();
	void FreeExtent(CLExtent * pExtent);

private:
	CLExtent * NewAExtent();
	void DeleteAExtent(CLExtent * pExtent);

private:
	std::stack<CLExtent *> m_extents;
	unsigned int m_freeExtentCount;
	static const unsigned int MAX_CACHE_EXTENT_COUNT = 1024;
	static const unsigned int REST_EXTENT_RATE_BIT = 1;
};

#endif