#include "CLLogArea.h"
#include <cassert>

NS_BEGIN

CLLogArea::CLLogArea(int index, void * pNVMAddress, unsigned int size):
m_index(index),
m_pStartAddress(pNVMAddress),
m_pCurrentWriteAddress(((unsigned long)m_pStartAddress) + sizeof(unsigned long))
{
}

CLLogArea::~CLLogArea()
{
}

unsigned long CLLogArea::TryGetAndIncreaseCurrentWriteAddress(unsigned long writeLogSize)
{
	unsigned long writtenSize = m_pCurrentWriteAddress - (unsigned long)(m_pStartAddress);
	if ((writtenSize + writeLogSize) >= (LOG_AREA_SIZE - sizeof(unsigned long)))
	{
		return 0;
	}
	unsigned long oldCurrentWriteAddress = m_pCurrentWriteAddress;
	m_pCurrentWriteAddress += writeLogSize;
	return oldCurrentWriteAddress;
}

void CLLogArea::Recovery(void * pLogArea)
{
	assert(pLogArea);
	unsigned long validFlag = *(unsigned long *)pLogArea;
	if (validFlag == 0)
	{
		return;
	}
	CLLogItem::Recovery((unsigned long)pLogArea + sizeof(unsigned long));
}

NS_END