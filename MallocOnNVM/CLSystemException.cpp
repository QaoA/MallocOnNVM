#include "CLSystemException.h"

CLSystemException::CLSystemException(int errorType):
m_err(errorType)
{
}

CLSystemException::~CLSystemException()
{
}
