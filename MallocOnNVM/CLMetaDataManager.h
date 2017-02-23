#ifndef __METADATA_MANAGER_H__
#define __METADATA_MANAGER_H__

#include "CLPerArenaBlockManager.h"
#include "CLExtentManager.h"

class CLExtent;

class CLMetaDataManager
{
public:
	CLMetaDataManager();
	~CLMetaDataManager();

public:
	CLExtent * GetExtent();
	CLExtent * AllocANVMBlockForExtent(CLExtent * pExtent);
	void FreeExtent(CLExtent * pExtent);
	void FreeNVMBlockForExtent(CLExtent * pExtent);

private:
	CLPerArenaBlockManager m_blockManager;
	CLExtentManager m_extentManager;
};

#endif