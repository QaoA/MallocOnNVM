#include "CLArenaManager.h"
#include "CLArena.h"
#include "CLCriticalSection.h"
#include <sys/sysinfo.h>
#include <cstring>
#include <cassert>
#include <limits.h>

CLArenaManager::CLArenaManager():
m_arenaArray(nullptr),
m_arenaCurrentCount(0),
m_arenaMaxCount(0),
m_currentThreadArena(CallbackAreanDestruct)
{
	m_arenaMaxCount = get_nprocs() * 4;
	m_arenaArray = new CLArena * [m_arenaMaxCount];
	memset(m_arenaArray, 0, sizeof(CLArena *)*m_arenaMaxCount);
}

CLArenaManager::~CLArenaManager()
{
}

CLArenaManager * CLArenaManager::GetInstance()
{
	static CLArenaManager instance;
	return &instance;
}

void CLArenaManager::CallbackAreanDestruct(void *)
{
	CLArenaManager::GetInstance()->GetArena()->Unbind();
}

CLArena * CLArenaManager::GetArena()
{
	CLArena * pArena = m_currentThreadArena.Get();
	if (pArena == nullptr)
	{
		CLArena * pNewArena = GetArenaFromArrayOrNewAArena();
		m_currentThreadArena.Set(pNewArena);
		pNewArena->Bind();
		return pNewArena;
	}
	return pArena;
}

CLArena * CLArenaManager::GetArena(unsigned int arenaId)
{
	assert(arenaId < m_arenaMaxCount);
	CLArena * pReturnArena = m_arenaArray[arenaId];
	assert(pReturnArena);
	return pReturnArena;
}

CLArena * CLArenaManager::GetArenaFromArrayOrNewAArena()
{
	CLArena * pNewArena = nullptr;
	CLArena * pReturnArena = nullptr;
	if (m_arenaCurrentCount <= m_arenaMaxCount)
	{
		pNewArena = new CLArena();
	}
	{
		CLCriticalSection cs(&m_arenaArrayLock);
		if (m_arenaCurrentCount >= m_arenaMaxCount)
		{
			pReturnArena = nullptr;
		}
		else
		{
			m_arenaArray[m_arenaCurrentCount] = pNewArena;
			pReturnArena = pNewArena;
			pNewArena->SetArenaId(m_arenaCurrentCount);
			m_arenaCurrentCount++;
		}
	}
	if (pNewArena != pReturnArena)
	{
		delete pNewArena;
	}
	if (pReturnArena == nullptr)
	{
		pReturnArena = GetArenaFromArray();
	}
	return pReturnArena;
}

CLArena * CLArenaManager::GetArenaFromArray()
{
	assert(m_arenaCurrentCount >= m_arenaMaxCount);
	int minBindCount = INT_MAX;
	int minIndex = 0;
	for (int i = 0; i < m_arenaMaxCount; ++i)
	{
		unsigned int currentBindCount = m_arenaArray[i]->GetBindCount();
		if (currentBindCount < minBindCount)
		{
			minIndex = i;
			minBindCount = currentBindCount;
		}
	}
	return m_arenaArray[minIndex];
}