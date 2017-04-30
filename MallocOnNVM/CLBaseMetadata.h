#ifndef __BASE_METADATA_H__
#define __BASE_METADATA_H__

#include "CLLogAreaManager.h"
#include "CLNameServerArea.h"
#include "NVMMallocNameSpace.h"

NS_BEGIN

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
	CLNameServerArea * GetNameServer();

public:
	static unsigned long GetMetadataSize();

private:
	SLNVMBaseMetadata * m_baseData;
	CLLogAreaManager m_logAreaManager;
	CLNameServerArea m_nameServerArea;
};

NS_END

#endif