#ifndef __NVM_MALLOC_H__
#define __NVM_MALLOC_H__

#include <cstddef>
#include <memory>

class CLLogArea;
class CLNameServer;

void * MallocOnNVM(size_t size);
void FreeOnNVM(void * pNVMAddress);
void NotifyNVMMemoryGet(void * pNVMAddress);
void NotifyNVMMemoryRelease(void * pNVMAddress);
void Recovery();
CLLogArea * AllocLogArea();
void FreeLogArea(CLLogArea * pArea);
CLNameServer * GetNameServer();

#endif