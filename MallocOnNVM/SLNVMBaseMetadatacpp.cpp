#include "SLNVMBaseMetadata.h"
#include <cassert>

size_t SLNVMBaseMetadata::GetClassSize()
{
	assert(sizeof(SLNVMBaseMetadata) <= PAGE_SIZE);
	return PAGE_SIZE;
}