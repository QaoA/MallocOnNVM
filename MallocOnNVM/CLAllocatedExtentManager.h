#ifndef __ALLOCATED_EXTENT_MANAGER_H__
#define __ALLOCATED_EXTENT_MANAGER_H__

#include "CLRadixTree.h"
#include "NVMMallocNameSpace.h"

NS_BEGIN

class CLExtent;

class CLAllocatedExtentManager
{
public:
	CLAllocatedExtentManager();
	~CLAllocatedExtentManager();

public:
	static CLAllocatedExtentManager * GetInstance();

public:
	void Put(CLExtent * pExtent);
	CLExtent * Remove(void * pNVMAddress);
	CLExtent * Get(void * pNVMAddress);

private:
	CLRadixTree<CLExtent> m_extentTree;
};

NS_END
#endif