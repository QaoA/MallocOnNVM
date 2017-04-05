#include "CLNameServer.h"
#include "CLCriticalSection.h"
#include <cassert>
#include <cstring>

using namespace std;

CLNameServer::CLNameServer(SLNVMNameServer * pNameServer):
m_pNameServer(pNameServer)
{
	assert(pNameServer);
	for (int i = 0; i < MAX_NAME_ADDRESS_PAIR_COUNT; ++i)
	{
		if (pNameServer->m_pairs[i].m_name[0] == '\0')
		{
			m_availableIndexArray.push_back(i);
		}
	}
}

CLNameServer::~CLNameServer()
{
}

std::shared_ptr<CLLogItem<sizeof(SLNameAddressPair)>> CLNameServer::Set(SLNameAddressPair & pair, int & nameServerIndex)
{
	CLCriticalSection cs(&m_lock);
	int index = -1;
	for (int i = 0; i < MAX_NAME_ADDRESS_PAIR_COUNT; ++i)
	{
		if(strcmp(&m_pNameServer->m_pairs[i].m_name[i], pair.m_name) == 0)
		{
			index = i;
			break;
		}
	}
	if (index == -1)
	{
		if (m_availableIndexArray.empty())
		{
			return shared_ptr<CLLogItem<sizeof(SLNameAddressPair)> >();
		}
		index = m_availableIndexArray.front();
		m_availableIndexArray.pop_front();
		nameServerIndex = index;
	}
	return shared_ptr<CLLogItem<sizeof(SLNameAddressPair)> >(new CLLogItem<sizeof(SLNameAddressPair)>(&m_pNameServer->m_pairs[index], &pair));
}

void * CLNameServer::Get(char * name)
{
	CLCriticalSection cs(&m_lock);
	for (int i = 0; i < MAX_NAME_ADDRESS_PAIR_COUNT; ++i)
	{
		if (strcmp(&m_pNameServer->m_pairs[i].m_name[i], name) == 0)
		{
			return m_pNameServer->m_pairs[i].m_pNameAddress;
		}
	}
	return nullptr;
}

void CLNameServer::SetAbort(int index)
{
	CLCriticalSection cs(&m_lock);
	m_availableIndexArray.push_back(index);
}