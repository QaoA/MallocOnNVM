#ifndef __ARENA_H__
#define __ARENA_H__

#include "CLSmallExtentManager.h"
#include "CLLargeExtentManager.h"
#include "CLHugeExtentManager.h"
#include "CLPerArenaBlockManager.h"
#include "CLMutex.h"
#include "NVMMallocNameSpace.h"
#include <cstddef>

NS_BEGIN
class CLExtent;

class CLArena
{
public:
	CLArena(unsigned int arenaId);
	~CLArena();

public:
	CLExtent * GetExtent(size_t size);
	void FreeExtent(CLExtent * pExtent);
	void Bind();
	void Unbind();
	unsigned int GetBindCount();
	unsigned int GetArenaId();

public:
	void RecieveBlockAreaRecovery(CLBlockArea * pBlockArea);
	void RecieveExtentRecovery(CLExtent * pExtent);

private:
	unsigned int m_arenaId;
	CLSmallExtentManager m_smallManager;
	CLLargeExtentManager m_largeManager;
	CLHugeExtentManager m_hugeManager;
	CLPerArenaBlockManager m_blockManager;
	CLMutex m_allocMutex;
	CLMutex m_bindMutex;
	unsigned int m_bindCount;
};

NS_END
#endif