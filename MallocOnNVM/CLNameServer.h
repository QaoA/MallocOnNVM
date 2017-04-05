#ifndef __NAME_SERVER_H__
#define __NAME_SERVER_H__

#include "SLNVMNameServer.h"
#include "CLLogItem.h"
#include "CLSpinLock.h"
#include <memory>
#include <list>

class CLNameServer
{
public:
	CLNameServer(SLNVMNameServer * pNameServer);
	~CLNameServer();

public:
	std::shared_ptr<CLLogItem<sizeof(SLNameAddressPair)> > Set(SLNameAddressPair & pair, int & nameServerIndex);
	void * Get(char * name);
	void SetAbort(int index);

private:
	SLNVMNameServer * m_pNameServer;
	CLSpinLock m_lock;
	std::list<int> m_availableIndexArray;
};

#endif