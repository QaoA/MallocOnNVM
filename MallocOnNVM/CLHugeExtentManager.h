#ifndef __HUGE_EXTENT_MANAGER_H__
#define __HUGE_EXTENT_MANAGER_H__

#include "NVMMallocNameSpace.h"
#include <cstddef>

NS_BEGIN

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

NS_END
#endif