#ifndef __PER_ARENA_BLOCK_AREA_MANAGER_H__
#define __PER_ARENA_BLOCK_AREA_MANAGER_H__

#include <list>

class CLBlockArea;
class CLExtent;

class CLPerArenaBlockManager
{
public:
	CLPerArenaBlockManager();
	~CLPerArenaBlockManager();

public:
	CLExtent * AllocBlockForExtent(CLExtent * pExtent);
	void FreeBlockForExtent(CLExtent * pExtent);

private:
	std::list<CLBlockArea *> m_NonFullAreaList;
	std::list<CLBlockArea *> m_FullAreaList;
	unsigned int m_nonFullAreasCount;
};

#endif