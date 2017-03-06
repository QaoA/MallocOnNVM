#include "SLNVMBlock.h"
#include <cassert>
#include <cstring>

void SLNVMBlock::SetData(void * pAddress, size_t size, unsigned int arenaId)
{
	m_pAddress = pAddress;
	m_size = size;
	m_arenaId = arenaId;
}

bool SLNVMBlock::IsAvailable()
{
	return !m_referenceCount;
}

void SLNVMBlock::Format()
{
	memset(this, 0, sizeof(SLNVMBlock));
}

void SLNVMBlock::MakeFree()
{
	m_pAddress = nullptr;
}

void SLNVMBlock::IncreaseReferenceCount()
{
	++m_referenceCount;
}

void SLNVMBlock::DecreaseReferenceCount()
{
	--m_referenceCount;
}

unsigned int SLNVMBlock::GetReferenceCount()
{
	return m_referenceCount;
}