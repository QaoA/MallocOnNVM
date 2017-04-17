#include "CLArenaManager.h"
#include "CLArena.h"
#include "CLCriticalSection.h"
#include <sys/sysinfo.h>
#include <cstring>
#include <cassert>
#include <limits.h>

NS_BEGIN
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

void CLArenaManager::CallbackAreanDestruct(void * pArena)
{
	static_cast<CLArena *>(pArena)->Unbind();
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
	if (pReturnArena == nullptr)
	{
		CLCriticalSection cs(&m_arenaArrayLock);
		if (pReturnArena == nullptr)
		{
			m_arenaArray[arenaId] = new CLArena(arenaId);
		}
		pReturnArena = m_arenaArray[arenaId];
	}
	assert(pReturnArena);
	return pReturnArena;
}

CLArena * CLArenaManager::GetArenaRecovery(unsigned int arenaId)
{
	assert(arenaId < m_arenaMaxCount);
	CLArena * pReturnArena = m_arenaArray[arenaId];
	if (pReturnArena == nullptr)
	{
		CLCriticalSection cs(&m_arenaArrayLock);
		assert(arenaId >= m_arenaCurrentCount);
		for (int i = m_arenaCurrentCount; i <= arenaId; ++i)
		{
			if (m_arenaArray[i] == nullptr)
			{
				m_arenaArray[i] = new CLArena(i);
			}
		}
		m_arenaCurrentCount = arenaId;
	}
	return m_arenaArray[arenaId];
}

CLArena * CLArenaManager::GetArenaFromArrayOrNewAArena()
{
	CLArena * pReturnArena = nullptr;
	pReturnArena = TryNewAArena();
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
	CLCriticalSection cs(&m_arenaArrayLock);
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

CLArena * CLArenaManager::TryNewAArena()
{
	CLArena * pReturnArena = nullptr;
	CLCriticalSection cs(&m_arenaArrayLock);
	if (m_arenaCurrentCount >= m_arenaMaxCount)
	{
		pReturnArena = nullptr;
	}
	else
	{
		pReturnArena = new CLArena(m_arenaCurrentCount);
		m_arenaArray[m_arenaCurrentCount] = pReturnArena;
		m_arenaCurrentCount++;
	}
	return pReturnArena;
}

NS_END