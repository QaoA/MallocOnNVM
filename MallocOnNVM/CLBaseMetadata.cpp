#include "CLBaseMetadata.h"
#include "SLNVMBaseMetadata.h"
#include <cassert>

CLBaseMetadata::CLBaseMetadata(SLNVMBaseMetadata * pBaseData) :
m_baseData(pBaseData),
m_logAreaManager(&pBaseData->m_data.m_logAreaPointers)
{
}

CLBaseMetadata::~CLBaseMetadata()
{
}

void CLBaseMetadata::Recovery(LogRecoveryFunc recoveryFunc, CLRecoverier & recoverier)
{
	m_logAreaManager.Recovery(recoveryFunc,recoverier);
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

CLLogAreaManager * CLBaseMetadata::GetLogAreaManager()
{
	return &m_logAreaManager;
}

unsigned long CLBaseMetadata::GetMetadataSize()
{
	return sizeof(SLNVMBaseMetadata);
}