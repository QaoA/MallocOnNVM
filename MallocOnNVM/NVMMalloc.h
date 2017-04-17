#ifndef __NVM_MALLOC_H__
#define __NVM_MALLOC_H__

#include <cstddef>
#include <memory>
#include "NVMMallocNameSpace.h"

NS_BEGIN

class CLLogArea;
class CLNameServer;

void * MallocOnNVM(size_t size);
void FreeOnNVM(void * pNVMAddress);
void NotifyNVMMemoryGet(void * pNVMAddress);
void NotifyNVMMemoryRelease(void * pNVMAddress);
unsigned int * GetReferenceCountAddress(void * pNVMAddress);
void Recovery();
CLLogArea * AllocLogArea();
void FreeLogArea(CLLogArea * pArea);
CLNameServer * GetNameServer();

NS_END
#endif