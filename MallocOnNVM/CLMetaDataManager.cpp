#include "CLMetaDataManager.h"
#include "CLBlockArea.h"
#include "CLExtent.h"
#include <cassert>

using namespace std;

CLMetaDataManager::CLMetaDataManager()
{
}

CLMetaDataManager::~CLMetaDataManager()
{
}

CLExtent * CLMetaDataManager::GetExtent()
{
	return m_extentManager.GetExtent();
}

CLExtent * CLMetaDataManager::AllocANVMBlockForExtent(CLExtent * pExtent, unsigned int arenaId)
{
	assert(pExtent && !pExtent->IsOccupied());
	return m_blockManager.AllocBlockForExtent(pExtent,arenaId);
}

void CLMetaDataManager::FreeExtent(CLExtent * pExtent)
{
	assert(pExtent);
	m_extentManager.FreeExtent(pExtent);
}

void CLMetaDataManager::FreeNVMBlockForExtent(CLExtent * pExtent)
{
	assert(pExtent);
	m_blockManager.FreeBlockForExtent(pExtent);
	pExtent->SetRelease();
}