#ifndef __SEMAPHORE_H__
#define __SEMAPHORE_H__

#include <semaphore.h>
#include <pthread.h>

class CLSemaphore
{
public:
	CLSemaphore(unsigned int value);
	~CLSemaphore();

public:
	void Wait();
	void Post();

private:
	sem_t m_sem;
};

#endif