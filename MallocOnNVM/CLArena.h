#ifndef __ARENA_H__
#define __ARENA_H__

#include "CLSmallExtentManager.h"
#include "CLLargeExtentManager.h"
#include "CLHugeExtentManager.h"
#include "CLMetaDataManager.h"
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
	void Bind();
	void Unbind();
	unsigned int GetBindCount();
	void SetArenaId(unsigned int id);
	unsigned int GetArenaId();

private:
	unsigned int m_arenaId;
	CLSmallExtentManager m_smallManager;
	CLLargeExtentManager m_largeManager;
	CLHugeExtentManager m_hugeManager;
	CLMetaDataManager m_metadataManager;
	CLMutex m_allocMutex;
	CLMutex m_bindMutex;
	unsigned int m_bindCount;
};

#endif