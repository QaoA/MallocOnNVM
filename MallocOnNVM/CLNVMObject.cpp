#include "CLNVMObject.h"
#include "CLExtent.h"
#include "NVMMalloc.h"

CLNVMObject::CLNVMObject(size_t size)
{
	m_extent = MallocOnNVM(size);
}

CLNVMObject::~CLNVMObject()
{
	FreeOnNVM(m_extent);
}

void CLNVMObject::Get()
{
	m_extent->IncreaseReferenceCount();
}

void CLNVMObject::Put()
{
	m_extent->DecreaseReferenceCount();
}

CLNVMObject::operator void *()
{
	return m_extent->GetNVMAddress();
}