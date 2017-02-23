#include "CLMutex.h"

CLMutex::CLMutex()
{
	pthread_mutex_init(&m_lock, NULL);
}

void CLMutex::Lock()
{
	pthread_mutex_lock(&m_lock);
}

void CLMutex::Unlock()
{
	pthread_mutex_unlock(&m_lock);
}

bool CLMutex::TryLock()
{
	return !pthread_mutex_trylock(&m_lock);
}

CLMutex::~CLMutex()
{
	pthread_mutex_destroy(&m_lock);
}
