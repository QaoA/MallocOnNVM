#ifndef __NVM_LOG_AREA_POINTERS_H__
#define __NVM_LOG_AREA_POINTERS_H__

#include "NVMMallocNameSpace.h"

NS_BEGIN

#define LOG_AREA_ARRAY_SIZE 64

struct SLNVMLogAreaPointers
{
public:
	void * m_logAreaArray[LOG_AREA_ARRAY_SIZE];

public:
	static int GetMaxAreaPointerCount();
};

NS_END
#endif