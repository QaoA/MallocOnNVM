#ifndef __SPIN_LOCK_H__
#define __SPIN_LOCK_H__

class CLSpinLock
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