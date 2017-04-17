#include "CLSystemException.h"

NS_BEGIN

CLSystemException::CLSystemException(int errorType):
m_err(errorType)
{
}

CLSystemException::~CLSystemException()
{
}

NS_END