#ifndef __SYSTEM_EXCEPTION_H__
#define __SYSTEM_EXCEPTION_H__

#define FILE_OPEN_ERROR 0
#define FILE_MAP_ERROR 1
#define FILE_MAP_ADDRESS_ERROR 2

class CLSystemException
{
public:
	CLSystemException(int errorType);
	~CLSystemException();

private:
	int m_err;
};

#endif