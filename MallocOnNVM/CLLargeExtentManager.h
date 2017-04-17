#ifndef __LARGE_EXTENT_MANAGER_H__
#define __LARGE_EXTENT_MANAGER_H__

#include "CLExtentList.h"
#include "SizeDefine.h"
#include "NVMMallocNameSpace.h"
#include <cstddef>

NS_BEGIN

class CLExtent;

class CLLargeExtentManager
{
public:
	CLLargeExtentManager();
	~CLLargeExtentManager();

public:
	CLExtent * GetAvailableExtent(size_t size);
	void FreeExtent(CLExtent * pExtent);
	
private:
	void AppendExtent(CLExtent * pExtent);
	CLExtent * MapNewExtent(size_t size);

private:
	unsigned int Size2Index(size_t size);
	size_t AlignSize(size_t size);

private:
	CLExtentList m_extentListArray[LARGE_OBJECT_ARRAY_SIZE];
};

NS_END
#endif