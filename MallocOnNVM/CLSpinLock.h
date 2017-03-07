#ifndef __SPIN_LOCK_H__
#define __SPIN_LOCK_H__

#include "ILLock.h"

class CLSpinLock:public ILLock
{
public:
	CLSpinLock();
	~CLSpinLock();

public:
	virtual bool TryLock();
	virtual void Lock();
	virtual void Unlock();

private:
	bool m_lock;
};

#endif