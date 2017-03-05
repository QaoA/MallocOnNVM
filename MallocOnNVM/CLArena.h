#ifndef __ARENA_H__
#define __ARENA_H__

#include "CLSmallExtentManager.h"
#include "CLLargeExtentManager.h"
#include "CLHugeExtentManager.h"
#include "CLMutex.h"
#include <cstddef>

class CLExtent;

class CLArena
{
public:
	CLArena();
	~CLArena();

public:
	CLExtent * GetExtent(size_t size);
	void FreeExtent(CLExtent * pExtent);

private:
	CLSmallExtentManager m_smallManager;
	CLLargeExtentManager m_largeManager;
	CLHugeExtentManager m_hugeManager;
	CLMutex m_mutex;
};

#endif