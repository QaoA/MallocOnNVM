#include "CLLogArea.h"

NS_BEGIN

CLLogArea::CLLogArea(int index, void * pNVMAddress, unsigned int size):
m_index(index),
m_writeFlag(false),
m_pStartAddress(pNVMAddress),
m_pCurrentWriteAddress(((unsigned long)m_pStartAddress) + sizeof(unsigned long))
{
}

CLLogArea::~CLLogArea()
{
}

bool CLLogArea::WriteLog(void * pAddress, unsigned int size, void * value)
{
	if (!m_writeFlag)
	{
		return false;
	}
	if (CanWrite(size + sizeof(void *) + sizeof(unsigned int)))
	{
		*(void **)(m_pCurrentWriteAddress) = pAddress;
		m_pCurrentWriteAddress += sizeof(void *);
		*(unsigned int *)(m_pCurrentWriteAddress) = size;
		m_pCurrentWriteAddress += sizeof(unsigned int);
		memcpy((void *)(m_pCurrentWriteAddress), value, size);
		m_pCurrentWriteAddress += size;
		*(void **)(m_pCurrentWriteAddress) = nullptr;
		return true;
	}
	return false;
}

void CLLogArea::Recovery(void * pLogArea)
{
	unsigned long logStartAddress = (unsigned long)(pLogArea)+sizeof(unsigned long);
	unsigned long validFlag = *(unsigned long *)(logStartAddress);
	if (validFlag == 0)
	{
		return;
	}
	while (*(void **)(logStartAddress) != nullptr)
	{
		void * pAddress = *(void **)(logStartAddress);
		logStartAddress += sizeof(void *);
		unsigned int size = *(unsigned int *)(logStartAddress);
		logStartAddress += sizeof(unsigned int);
		memcpy((void *)pAddress, (void *)logStartAddress, size);
		logStartAddress += size;
	}
	*(unsigned long *)(logStartAddress) = 0;
}

NS_END