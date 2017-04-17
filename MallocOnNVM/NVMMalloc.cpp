#include "NVMMalloc.h"
#include "CLArenaManager.h"
#include "CLArena.h"
#include "CLExtent.h"
#include "CLAllocatedExtentManager.h"
#include "CLNVMMemoryMapManager.h"
#include "CLBaseMetadata.h"
#include "CLRecoverier.h"

NS_BEGIN

using namespace std;

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

unsigned int * GetReferenceCountAddress(void * pNVMAddress)
{
	CLExtent * pExtent = CLAllocatedExtentManager::GetInstance()->Get(pNVMAddress);
	if (pExtent)
	{
		return pExtent->GetNVMReferenceCountAddress();
	}
	else
	{
		return nullptr;
	}
}

void Recovery()
{
	CLRecoverier r;
	r.DoRecovery();
}

CLLogArea * AllocLogArea()
{
	return CLNVMMemoryMapManager::GetInstance()->GetBaseMetadata()->GetLogAreaManager()->GetArea();
}

void FreeLogArea(CLLogArea * pArea)
{
	assert(pArea);
	CLNVMMemoryMapManager::GetInstance()->GetBaseMetadata()->GetLogAreaManager()->FreeArea(pArea);
}

CLNameServer * GetNameServer()
{
	return CLNVMMemoryMapManager::GetInstance()->GetBaseMetadata()->GetNameServer();
}

NS_END