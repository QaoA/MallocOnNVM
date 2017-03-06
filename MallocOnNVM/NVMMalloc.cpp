#include "NVMMalloc.h"
#include "CLArenaManager.h"
#include "CLArena.h"
#include "CLExtent.h"

CLExtent * MallocOnNVM(size_t size)
{
	return CLArenaManager::GetInstance()->GetArena()->GetExtent(size);
}

void FreeOnNVM(CLExtent * pExtent)
{
	if (pExtent == nullptr)
	{
		return;
	}
	CLArenaManager::GetInstance()->GetArena(pExtent->GetArenaId())->FreeExtent(pExtent);
}