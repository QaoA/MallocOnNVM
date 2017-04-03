#ifndef __NVM_MALLOC_H__
#define __NVM_MALLOC_H__

#include <cstddef>
#include "CLRecoverier.h"

void * MallocOnNVM(size_t size);
void FreeOnNVM(void * pNVMAddress);
void NotifyNVMMemoryGet(void * pNVMAddress);
void NotifyNVMMemoryRelease(void * pNVMAddress);
void Recovery(LogRecoveryFunc recoveryFunc);

#endif