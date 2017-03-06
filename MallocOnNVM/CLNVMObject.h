#ifndef __NVM_OBJECT_H__
#define __NVM_OBJECT_H__

#include <cstddef>

class CLExtent;

class CLNVMObject
{
public:
	CLNVMObject(size_t allocateSize);
	~CLNVMObject();

public:
	void Get();
	void Put();
	operator void * ();

private:
	CLExtent * m_extent;
};

#endif