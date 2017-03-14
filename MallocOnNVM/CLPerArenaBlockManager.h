#ifndef __PER_ARENA_BLOCK_AREA_MANAGER_H__
#define __PER_ARENA_BLOCK_AREA_MANAGER_H__

#include <list>

class CLBlockArea;
class CLBlock;

#define CACHE_EMPTY_AREA_MAX_COUNT 8
#define EMPTY_AREA_PURGE_BIT 2

class CLPerArenaBlockManager
{
public:
	CLPerArenaBlockManager();
	~CLPerArenaBlockManager();

public:
	CLBlock * AllocBlock();
	void FreeBlock(CLBlock * pBlock);

public:
	void RecieveBlockAreaRecovery(CLBlockArea * pBlockArea);

private:
	std::list<CLBlockArea *> m_nonFullAreaList;
	std::list<CLBlockArea *> m_fullAreaList;
	std::list<CLBlockArea *> m_emptyAreaList;
	unsigned int m_emptyAreaCount;
};

#endif