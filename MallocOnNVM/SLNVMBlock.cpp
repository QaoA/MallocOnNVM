#include "SLNVMBlock.h"
#include <cassert>
#include <cstring>

void SLNVMBlock::SetAddress(void * pAddress, size_t size)
{
	m_pAddress = pAddress;
	m_size = size;
}

bool SLNVMBlock::IsAvailable()
{
	return !m_referenceCount;
}

void SLNVMBlock::Format()
{
	memset(this, 0, sizeof(SLNVMBlock));
}