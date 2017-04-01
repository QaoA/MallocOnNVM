#ifndef __LOG_AREA_H__
#define __LOG_AREA_H__

struct SLNVMLogArea;

class CLLogArea
{
public:
	CLLogArea(SLNVMLogArea * pLogArea);
	~CLLogArea();

public:
	SLNVMLogArea * m_pLogArea;
};

#endif