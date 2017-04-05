#ifndef __NAME_ADDRESS_PAIR_H__
#define __NAME_ADDRESS_PAIR_H__

#define NAME_MAX_SIZE 24

struct SLNameAddressPair
{
public:
	char m_name[NAME_MAX_SIZE];
	void * m_pNameAddress;
};

#endif