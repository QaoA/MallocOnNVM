#ifndef __BASE_METADATA_H__
#define __BASE_METADATA_H__

#include "CLLogAreaManager.h"

struct SLNVMBaseMetadata;
struct SLNVMBlockArea;
class CLRecoverier;

class CLBaseMetadata
{
public:
	CLBaseMetadata(SLNVMBaseMetadata * pBaseData);
	~CLBaseMetadata();

public:
	void Recovery(LogRecoveryFunc recoveryFunc, CLRecoverier & recoverier);
	SLNVMBlockArea * GetFirstBlockArea();
	void SetFirstBlockArea(SLNVMBlockArea * pFirstArea);
	CLLogAreaManager * GetLogAreaManager();

public:
	static unsigned long GetMetadataSize();

private:
	SLNVMBaseMetadata * m_baseData;
	CLLogAreaManager m_logAreaManager;
};

#endif