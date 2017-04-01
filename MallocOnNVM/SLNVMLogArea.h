#ifndef __NVM_LOG_AREA_H__
#define __NVM_LOG_AREA_H__

#include "SizeDefine.h"

#define LOG_AREA_SIZE PAGE_SIZE

struct SLNVMLogArea
{
public:
	char m_logArea[LOG_AREA_SIZE];
};

#endif