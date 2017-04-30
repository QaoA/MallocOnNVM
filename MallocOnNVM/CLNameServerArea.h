#ifndef __NAME_SERVER_AREA_H__
#define __NAME_SERVER_AREA_H__

#include "NVMMallocNameSpace.h"

NS_BEGIN

struct SLNVMNameServerArea;

class CLNameServerArea
{
public:
	CLNameServerArea(SLNVMNameServerArea * pArea);
	~CLNameServerArea();

public:
	inline void * GetAreaStartAddress();
	unsigned int GetAreaSize();

private:
	 SLNVMNameServerArea * m_address;
};

inline void * CLNameServerArea::GetAreaStartAddress()
{
	return m_address;
}
NS_END
#endif