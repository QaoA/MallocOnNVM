#ifndef __TLS_VARIABLE_H__
#define  __TLS_VARIABLE_H__

#include <pthread.h>

typedef void(*TLSDestructorFunc)(void*);

template<class T>
class CLTLSVariable
{
public:
	CLTLSVariable(TLSDestructorFunc func = nullptr);
	~CLTLSVariable();

public:
	void Set(T * value);
	T * Get();

private:
	pthread_key_t m_key;
};

template<class T>
CLTLSVariable<T>::CLTLSVariable(TLSDestructorFunc func)
{
	pthread_key_create(&m_key,func);
}

template<class T>
CLTLSVariable<T>::~CLTLSVariable()
{
	pthread_key_delete(m_key);
}

template<class T>
void CLTLSVariable<T>::Set(T * value)
{
	pthread_setspecific(m_key, value);
}

template<class T>
T* CLTLSVariable<T>::Get()
{
	return static_cast<T*>(pthread_getspecific(m_key));
}

#endif