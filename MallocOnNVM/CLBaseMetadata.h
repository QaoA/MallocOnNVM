#ifndef __BASE_METADATA_H__
#define __BASE_METADATA_H__

#include "CLLogAreaManager.h"
#include "CLNameServer.h"

struct SLNVMBaseMetadata;
struct SLNVMBlockArea;
class CLRecoverier;

class CLBaseMetadata
{
public:
	CLBaseMetadata(SLNVMBaseMetadata * pBaseData);
	~CLBaseMetadata();

public:
	void Recovery(CLRecoverier & recoverier);
	SLNVMBlockArea * GetFirstBlockArea();
	void SetFirstBlockArea(SLNVMBlockArea * pFirstArea);
	CLLogAreaManager * GetLogAreaManager();
	CLNameServer * GetNameServer();

public:
	static unsigned long GetMetadataSize();

private:
	SLNVMBaseMetadata * m_baseData;
	CLLogAreaManager m_logAreaManager;
	CLNameServer m_nameServer;
};

#endif