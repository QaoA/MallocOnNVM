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

CLExtent * CLMetaDataManager::AllocANVMBlockForExtent(CLExtent * pExtent)
{
	assert(pExtent && !pExtent->IsOccupied());
	return m_blockManager.AllocBlockForExtent(pExtent);
}

void CLMetaDataManager::FreeNVMBlockForExtent(CLExtent * pExtent)
{
	assert(pExtent);
	m_blockManager.FreeBlockForExtent(pExtent);
	pExtent->SetRelease();
}