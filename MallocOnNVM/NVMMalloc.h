#ifndef __NVM_MALLOC_H__
#define __NVM_MALLOC_H__

//֪ͨ��ʽʵ�ֵĻ���
//���߳�ȥ����

#include <cstddef>

class CLExtent;

CLExtent * MallocOnNVM(size_t size);
void FreeOnNVM(CLExtent * pExtent);

#endif