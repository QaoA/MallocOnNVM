#ifndef __NVM_BASE_METADATA_H__
#define __NVM_BASE_METADATA_H__

#include "SizeDefine.h"
#include "SLNVMLogAreaPointers.h"
#include "SLNVMNameServerArea.h"
#include "NVMMallocNameSpace.h"
#include <cstddef>

NS_BEGIN

struct SLNVMBlockArea;
class CLBaseMetadata;

#define NVM_BASE_METADATA_SIZE PAGE_SIZE

struct SLNVMBaseMetadata
{
	friend class CLBaseMetadata;

public:
	static size_t GetClassSize();

private:
	struct SLData
	{
		SLNVMBlockArea * m_pFirstArea;
		SLNVMLogAreaPointers m_logAreaPointers;
		SLNVMNameServerArea m_nameServer;
	};
	union
	{
		SLData m_data;
		char m_sizeArray[NVM_BASE_METADATA_SIZE];
	};
};

NS_END
#endif