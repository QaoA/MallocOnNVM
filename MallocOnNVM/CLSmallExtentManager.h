#ifndef __SMALL_EXTENT_MANAGER_H__
#define __SMALL_EXTENT_MANAGER_H__

#include "CLExtentList.h"
#include "SizeDefine.h"
#include <cstddef>

class CLExtent;
class CLMetaDataManager;

class CLSmallExtentManager
{
public:
	CLSmallExtentManager();
	~CLSmallExtentManager();

public:
	CLExtent * GetAvailableExtent(size_t expectedSize, CLMetaDataManager * pMetadataManager);

private:
	void SetCurrentExtent(size_t expectedSize, CLMetaDataManager * pMetadataManager);
	void AppendExtent(CLExtent * pExtent);
	CLExtent * MapANewExtent(CLMetaDataManager * pMetadataManager);
	CLExtent * SplitExtent(CLExtent * pTargetExtent, size_t expectedSize, CLMetaDataManager * pMetadataManager);
	unsigned int Size2Index(size_t size);
	size_t Index2Size(unsigned int index);
	size_t AlignSize(size_t size);

private:
	CLExtent * m_pCurrentExtent;
	CLExtent * m_pLastExtent;
	CLExtentList m_ExtentLists[SMALL_OBJECT_ARRAY_SIZE];
};

#endif