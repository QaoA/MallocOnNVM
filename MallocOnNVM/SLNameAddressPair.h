#ifndef __NAME_ADDRESS_PAIR_H__
#define __NAME_ADDRESS_PAIR_H__

#include "NVMMallocNameSpace.h"

NS_BEGIN

#define NAME_MAX_SIZE 24

struct SLNameAddressPair
{
public:
	char m_name[NAME_MAX_SIZE];
	void * m_pNameAddress;
};

NS_END
#endif