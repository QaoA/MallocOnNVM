#include "NVMMalloc.h"
#include "CLArenaManager.h"
#include "CLArena.h"
#include "CLExtent.h"
#include "CLAllocatedExtentManager.h"
#include "CLRecoverier.h"

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
	CLExtent * pExtent = CLAllocatedExtentManager::GetInstance()->Remove(pNVMAddress);
	if (pExtent)
	{
		CLArenaManager::GetInstance()->GetArena(pExtent->GetArenaId())->FreeExtent(pExtent);
	}
}

void NotifyNVMMemoryGet(void * pNVMAddress)
{
	CLExtent * pExtent = CLAllocatedExtentManager::GetInstance()->Get(pNVMAddress);
	if (pExtent)
	{
		pExtent->IncreaseReferenceCount();
	}
}

void NotifyNVMMemoryRelease(void * pNVMAddress)
{
	CLExtent * pExtent = CLAllocatedExtentManager::GetInstance()->Get(pNVMAddress);
	if (pExtent)
	{
		pExtent->DecreaseReferenceCount();
	}
}

void Recovery(LogRecoveryFunc recoveryFunc)
{
	CLRecoverier r;
	r.DoRecovery(recoveryFunc);
}