#ifndef __LARGE_EXTENT_MANAGER_H__
#define __LARGE_EXTENT_MANAGER_H__

#include "CLExtentList.h"
#include "SizeDefine.h"
#include <cstddef>

class CLExtent;
class CLMetaDataManager;

class CLLargeExtentManager
{
public:
	CLLargeExtentManager();
	~CLLargeExtentManager();

public:
	CLExtent * GetAvailableExtent(size_t size,CLMetaDataManager * pMetadataManager);
	void FreeExtent(CLExtent * pExtent,CLMetaDataManager * pMetadataManager);
	
private:
	void AppendExtent(CLExtent * pExtent, CLMetaDataManager * pMetadataManager);
	CLExtent * MapNewExtent(size_t size, CLMetaDataManager * pMetadataManager);

private:
	unsigned int Size2Index(size_t size);
	size_t AlignSize(size_t size);

private:
	CLExtentList m_extentListArray[LARGE_OBJECT_ARRAY_SIZE];
};

#endif