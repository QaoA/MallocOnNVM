#ifndef __NVM_BLOCK_H__
#define __NVM_BLOCK_H__

#include <cstddef>

struct SLNVMBlock
{
public:
	bool IsAvailable();
	void SetAddress(void * pAddress, size_t size);
	void Format();
	void MakeFree();

private:
	unsigned int m_referenceCount;
	size_t m_size;
	void * m_pAddress; 
};

#endif