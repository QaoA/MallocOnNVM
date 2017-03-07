#ifndef __ALLOCATED_EXTENT_MANAGER_H__
#define __ALLOCATED_EXTENT_MANAGER_H__

#include "CLRadixTree.h"

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
	CLExtent * Get(void * pNVMAddress);

private:
	CLRadixTree<CLExtent> m_extentTree;
};

#endif