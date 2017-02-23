#ifndef __MUTEX_H__
#define __MUTEX_H__

#include "ILLock.h"
#include <pthread.h>

class CLMutex:public ILLock
{
public:
	CLMutex();
	~CLMutex();

public:
	virtual void Lock();
	virtual void Unlock();
	virtual bool TryLock();

private:
	pthread_mutex_t m_lock;
};

#endif