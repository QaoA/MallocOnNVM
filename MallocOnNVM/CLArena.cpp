#include "CLArena.h"
#include "CLExtent.h"
#include "CLCriticalSection.h"
#include <cassert>

CLArena::CLArena():
m_arenaId(0),
m_smallManager(),
m_largeManager(),
m_hugeManager(),
m_metadataManager(),
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
	m_metadataManager.AllocANVMBlockForExtent(pExtent,m_arenaId);
	assert(pExtent->IsOccupied());
	return pExtent;
}

void CLArena::FreeExtent(CLExtent * pExtent)
{
	CLCriticalSection cs(&m_allocMutex);
	assert(pExtent);
	m_metadataManager.FreeNVMBlockForExtent(pExtent);
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

void CLArena::SetArenaId(unsigned int id)
{
	assert(m_arenaId == 0);
	m_arenaId = id;
}

unsigned CLArena::GetArenaId()
{
	return m_arenaId;
}