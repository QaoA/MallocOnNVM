#include "SLNVMBaseMetadata.h"
#include <cassert>

NS_BEGIN

size_t SLNVMBaseMetadata::GetClassSize()
{
	assert(sizeof(SLNVMBaseMetadata) <= PAGE_SIZE);
	return PAGE_SIZE;
}

NS_END