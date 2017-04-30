#ifndef __NVM_NAME_SERVER_AREA_H__
#define __NVM_NAME_SERVER_AREA_H__

#include "NVMMallocNameSpace.h"

NS_BEGIN

#define NVM_NAME_SERVER_AREA_SIZE 1024

struct SLNVMNameServerArea
{
	char m_data[NVM_NAME_SERVER_AREA_SIZE];
};

NS_END
#endif
