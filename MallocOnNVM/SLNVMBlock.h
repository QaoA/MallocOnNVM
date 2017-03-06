#ifndef __NVM_BLOCK_H__
#define __NVM_BLOCK_H__

#include <cstddef>

struct SLNVMBlock
{
public:
	bool IsAvailable();
	void SetData(void * pAddress, size_t size, unsigned int arenaId);
	void Format();
	void MakeFree();
	void IncreaseReferenceCount();
	void DecreaseReferenceCount();
	unsigned int GetReferenceCount();

private:
	unsigned int m_referenceCount;
	size_t m_size;
	void * m_pAddress;
	unsigned int m_arenaId;
};

#endif