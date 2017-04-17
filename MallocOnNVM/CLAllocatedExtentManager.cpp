#include "CLAllocatedExtentManager.h"
#include "CLExtent.h"

NS_BEGIN

CLAllocatedExtentManager::CLAllocatedExtentManager()
{
}

CLAllocatedExtentManager::~CLAllocatedExtentManager()
{
}

CLAllocatedExtentManager * CLAllocatedExtentManager::GetInstance()
{
	static CLAllocatedExtentManager instance;
	return &instance;
}

void CLAllocatedExtentManager::Put(CLExtent * pExtent)
{
	m_extentTree.Insert(pExtent, pExtent->GetNVMAddress());
}

CLExtent * CLAllocatedExtentManager::Get(void * pNVMAddress)
{
	return m_extentTree.Get(pNVMAddress);
}

CLExtent * CLAllocatedExtentManager::Remove(void * pNVMAddress)
{
	return m_extentTree.GetAndRemove(pNVMAddress);
}

NS_END