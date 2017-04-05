#include "CLBaseMetadata.h"
#include "SLNVMBaseMetadata.h"
#include <cassert>

CLBaseMetadata::CLBaseMetadata(SLNVMBaseMetadata * pBaseData) :
m_baseData(pBaseData),
m_logAreaManager(&pBaseData->m_data.m_logAreaPointers),
m_nameServer(&pBaseData->m_data.m_nameServer)
{
}

CLBaseMetadata::~CLBaseMetadata()
{
}

void CLBaseMetadata::Recovery(CLRecoverier & recoverier)
{
	m_logAreaManager.Recovery(recoverier);
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

CLNameServer * CLBaseMetadata::GetNameServer()
{
	return &m_nameServer;
}

unsigned long CLBaseMetadata::GetMetadataSize()
{
	return sizeof(SLNVMBaseMetadata);
}