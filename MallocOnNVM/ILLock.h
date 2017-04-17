#ifndef __LOCK_H__
#define __LOCK_H__

#include "NVMMallocNameSpace.h"

NS_BEGIN

class ILLock
{
public:
	virtual void Lock() = 0;
	virtual void Unlock() = 0;
	virtual bool TryLock() = 0;
};

NS_END
#endif