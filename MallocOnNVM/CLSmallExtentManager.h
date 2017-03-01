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
	void FreeExtent(CLExtent * pExtent, CLMetaDataManager * pMetadataManager);

private:
	void SetCurrentExtent(size_t expectedSize, CLMetaDataManager * pMetadataManager);
	void AppendExtent(CLExtent * pExtent);
	CLExtent * MapANewExtent(CLMetaDataManager * pMetadataManager);
	CLExtent * SplitExtent(CLExtent * pTargetExtent, size_t expectedSize, CLMetaDataManager * pMetadataManager);
	bool MergePreCheck(CLExtent * pPreviousExtent, CLExtent * pNextExtent);
	void RemoveExtentFromExtentListArray(CLExtent * pExtent);
	void AppendExtentToExtentListArray(CLExtent * pExtent);
	unsigned int Size2Index(size_t size);
	size_t Index2Size(unsigned int index);
	size_t AlignSize(size_t size);

private:
	CLExtent * m_pCurrentExtent;
	CLExtent * m_pLastExtent;
	CLExtentList m_ExtentListArray[SMALL_OBJECT_ARRAY_SIZE];
};

#endif