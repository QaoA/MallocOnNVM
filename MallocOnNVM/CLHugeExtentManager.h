#ifndef __HUGE_EXTENT_MANAGER_H__
#define __HUGE_EXTENT_MANAGER_H__

#include <cstddef>
#include "CLMetaDataManager.h"

class CLExtent;

class CLHugeExtentManager
{
public:
	CLHugeExtentManager();
	~CLHugeExtentManager();

public:
	CLExtent * GetAvailableExtent(size_t size,CLMetaDataManager * pMetadataManager);
	void FreeExtent(CLExtent * pExtent, CLMetaDataManager * pMetadataManager);

private:
	size_t AlignSize(size_t size);
};

#endif