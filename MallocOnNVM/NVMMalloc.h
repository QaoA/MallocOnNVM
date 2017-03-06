#ifndef __NVM_MALLOC_H__
#define __NVM_MALLOC_H__

//通知方式实现的回收
//此线程去回收

#include <cstddef>

class CLExtent;

CLExtent * MallocOnNVM(size_t size);
void FreeOnNVM(CLExtent * pExtent);

#endif