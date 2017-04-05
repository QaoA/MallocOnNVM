#ifndef __NVM_NAME_SERVER_H__
#define __NVM_NAME_SERVER_H__

#include "SLList.h"
#include "SLNameAddressPair.h"

#define NAME_SERVER_SIZE 1024
#define MAX_NAME_ADDRESS_PAIR_COUNT (NAME_SERVER_SIZE / sizeof(SLNameAddressPair))

struct SLNVMNameServer
{
public:
		SLNameAddressPair m_pairs[MAX_NAME_ADDRESS_PAIR_COUNT];
};

#endif