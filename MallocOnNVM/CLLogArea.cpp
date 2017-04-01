#include "CLLogArea.h"

CLLogArea::CLLogArea():
m_index(0),
m_pStartAddress(nullptr),
m_areaSize(0)
{
}

CLLogArea::CLLogArea(int index, void * pNVMAddress, unsigned int size):
m_index(index),
m_pStartAddress(pNVMAddress),
m_areaSize(size)
{
}

CLLogArea::~CLLogArea()
{
}

void CLLogArea::Init(int index, void * pNVMAddress, unsigned int size)
{
	m_index = index;
	m_pStartAddress = pNVMAddress;
	m_areaSize = size;
}
