#ifndef __HUGE_EXTENT_MANAGER_H__
#define __HUGE_EXTENT_MANAGER_H__

#include <cstddef>

class CLExtent;

class CLHugeExtentManager
{
public:
	CLHugeExtentManager();
	~CLHugeExtentManager();

public:
	CLExtent * GetAvailableExtent(size_t size);
	void FreeExtent(CLExtent * pExtent);

private:
	size_t AlignSize(size_t size);
};

#endif