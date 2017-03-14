#ifndef __ARENA_MANAGER_H__
#define __ARENA_MANAGER_H__

#include "CLTLSVariable.h"
#include "CLMutex.h"

class CLArena;

class CLArenaManager
{
private:
	CLArenaManager();
	CLArenaManager(const CLArenaManager &);
	CLArenaManager & operator=(const CLArenaManager &);
	~CLArenaManager();

public:
	static CLArenaManager * GetInstance();
	static void CallbackAreanDestruct(void *);

public:
	CLArena * GetArena();
	CLArena * GetArena(unsigned int arenaId);
	CLArena * GetArenaRecovery(unsigned int arenaId);

private:
	CLArena * GetArenaFromArrayOrNewAArena();
	CLArena * GetArenaFromArray();
	CLArena * TryNewAArena();

private:
	CLMutex m_arenaArrayLock;
	CLArena ** m_arenaArray;
	unsigned int m_arenaCurrentCount;
	unsigned int m_arenaMaxCount;
	CLTLSVariable<CLArena> m_currentThreadArena;
};

#endif