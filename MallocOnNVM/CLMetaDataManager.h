#ifndef __METADATA_MANAGER_H__
#define __METADATA_MANAGER_H__

#include "CLPerArenaBlockManager.h"

class CLExtent;

class CLMetaDataManager
{
public:
	CLMetaDataManager();
	~CLMetaDataManager();

public:
	CLExtent * AllocANVMBlockForExtent(CLExtent * pExtent, unsigned int arenaId);
	void FreeNVMBlockForExtent(CLExtent * pExtent);

private:
	CLPerArenaBlockManager m_blockManager;
};

#endif