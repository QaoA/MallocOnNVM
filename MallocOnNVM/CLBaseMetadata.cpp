#include "CLBaseMetadata.h"
#include "SLNVMBaseMetadata.h"
#include <cassert>

CLBaseMetadata::CLBaseMetadata(SLNVMBaseMetadata * pBaseData) :
m_baseData(pBaseData)
{
}

CLBaseMetadata::~CLBaseMetadata()
{
}

void CLBaseMetadata::SetBaseData(SLNVMBaseMetadata * pBaseMetadata)
{
	assert(pBaseMetadata);
	m_baseData = pBaseMetadata;
}

SLNVMBlockArea * CLBaseMetadata::GetFirstBlockArea()
{
	assert(m_baseData);
	return m_baseData->m_data.m_pFirstArea;
}

void CLBaseMetadata::SetFirstBlockArea(SLNVMBlockArea * pFirstArea)
{
	assert(m_baseData);
	m_baseData->m_data.m_pFirstArea = pFirstArea;
}

unsigned long CLBaseMetadata::GetMetadataSize()
{
	return sizeof(SLNVMBaseMetadata);
}