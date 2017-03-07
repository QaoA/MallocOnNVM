#include "NVMMalloc.h"
#include "CLArenaManager.h"
#include "CLArena.h"
#include "CLExtent.h"
#include "CLAllocatedExtentManager.h"

void * MallocOnNVM(size_t size)
{
	CLExtent * pExtent =  CLArenaManager::GetInstance()->GetArena()->GetExtent(size);
	if (pExtent != nullptr)
	{
		CLAllocatedExtentManager::GetInstance()->Put(pExtent);
	}
	return pExtent->GetNVMAddress();
}

void FreeOnNVM(void * pNVMAddress)
{
	if (pNVMAddress == nullptr)
	{
		return;
	}
	CLExtent * pExtent = CLAllocatedExtentManager::GetInstance()->Get(pNVMAddress);
	if (pExtent)
	{
		CLArenaManager::GetInstance()->GetArena(pExtent->GetArenaId())->FreeExtent(pExtent);
	}
}