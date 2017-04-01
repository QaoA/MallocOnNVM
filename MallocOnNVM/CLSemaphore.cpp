#include "CLSemaphore.h"

CLSemaphore::CLSemaphore(unsigned int value)
{
	sem_init(&m_sem, 0, value);
}

CLSemaphore::~CLSemaphore()
{
	sem_destroy(&m_sem);
}

void CLSemaphore::Wait()
{
	sem_wait(&m_sem);
}

void CLSemaphore::Post()
{
	sem_post(&m_sem);
}
