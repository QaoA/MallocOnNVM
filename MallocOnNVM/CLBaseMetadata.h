#ifndef __BASE_METADATA_H__
#define __BASE_METADATA_H__

struct SLNVMBaseMetadata;
struct SLNVMBlockArea;

class CLBaseMetadata
{
public:
	CLBaseMetadata(SLNVMBaseMetadata * pBaseData);
	~CLBaseMetadata();

public:
	void SetBaseData(SLNVMBaseMetadata * pBaseMetadata);
	SLNVMBlockArea * GetFirstBlockArea();
	void SetFirstBlockArea(SLNVMBlockArea * pFirstArea);

public:
	static unsigned long GetMetadataSize();

private:
	SLNVMBaseMetadata * m_baseData;
};

#endif