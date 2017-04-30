#ifndef __SYSTEM_EXCEPTION_H__
#define __SYSTEM_EXCEPTION_H__

#include "NVMMallocNameSpace.h"

NS_BEGIN

#define FILE_OPEN_ERROR 0
#define FILE_MAP_ERROR 1
#define FILE_MAP_ADDRESS_ERROR 2
#define SHM_OPEN_ERROR 3
#define SHM_TRUNCATE_ERROR 4

class CLSystemException
{
public:
	CLSystemException(int errorType);
	~CLSystemException();

private:
	int m_err;
};

NS_END
#endif