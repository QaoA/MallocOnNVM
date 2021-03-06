#include "CLArena.h"
#include "CLExtent.h"
#include "CLCriticalSection.h"
#include <cassert>

NS_BEGIN

CLArena::CLArena(unsigned int arenaId):
m_arenaId(arenaId),
m_smallManager(),
m_largeManager(),
m_hugeManager(),
m_blockManager(),
m_allocMutex(),
m_bindMutex(),
m_bindCount(0)
{
}

CLArena::~CLArena()
{
}

CLExtent * CLArena::GetExtent(size_t size)
{
	CLCriticalSection cs(&m_allocMutex);
	CLExtent * pExtent;
	if (size < SMALL_MAX_SIZE)
	{
		pExtent = m_smallManager.GetAvailableExtent(size);
	}
	else if (size < LARGE_MAX_SIZE)
	{
		pExtent = m_largeManager.GetAvailableExtent(size);
	}
	else
	{
		pExtent = m_hugeManager.GetAvailableExtent(size);
	}
	if (pExtent == nullptr)
	{
		return nullptr;
	}
	pExtent->SetOccupied(&m_blockManager, m_arenaId);
	assert(pExtent->IsOccupied());
	return pExtent;
}

void CLArena::FreeExtent(CLExtent * pExtent)
{
	CLCriticalSection cs(&m_allocMutex);
	assert(pExtent);
	pExtent->SetRelease(&m_blockManager);
	size_t size = pExtent->GetSize();
	if (size < SMALL_MAX_SIZE)
	{
		m_smallManager.FreeExtent(pExtent);
	}
	else if (size < LARGE_MAX_SIZE)
	{
		m_largeManager.FreeExtent(pExtent);
	}
	else
	{
		m_hugeManager.FreeExtent(pExtent);
	}
}

void CLArena::Bind()
{
	CLCriticalSection cs(&m_bindMutex);
	m_bindCount++;
}

void CLArena::Unbind()
{
	CLCriticalSection cs(&m_bindMutex);
	m_bindCount--;
}

unsigned int CLArena::GetBindCount()
{
	CLCriticalSection cs(&m_bindMutex);
	return m_bindCount;
}

unsigned int CLArena::GetArenaId()
{
	return m_arenaId;
}

void CLArena::RecieveBlockAreaRecovery(CLBlockArea * pBlockArea)
{
	assert(pBlockArea);
	m_blockManager.RecieveBlockAreaRecovery(pBlockArea);
}

void CLArena::RecieveExtentRecovery(CLExtent * pExtent)
{
	assert(pExtent);
	unsigned long size = pExtent->GetSize();
	if (size < SMALL_MAX_SIZE)
	{
		m_smallManager.RecieveExtentRecovery(pExtent);
	}
	else
	{
		assert(pExtent->IsOccupied());
	}
}

NS_END