#ifndef __NVM_MALLOC_H__
#define __NVM_MALLOC_H__

#include <cstddef>

class CLExtent;

void * MallocOnNVM(size_t size);
void FreeOnNVM(void * pNVMAddress);

#endif