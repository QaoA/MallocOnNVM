#ifndef __LOG_AREA_MANAGER_H__
#define __LOG_AREA_MANAGER_H__

#include "CLSemaphore.h"
#include "CLMutex.h"
#include "SizeDefine.h"
#include "NVMMallocNameSpace.h"
#include <list>
#include <memory>

NS_BEGIN

struct SLNVMLogAreaPointers;
class CLLogArea;
class CLRecoverier;

class CLLogAreaManager
{
public:
	CLLogAreaManager(SLNVMLogAreaPointers * pNVMLogAreaPointers);
	~CLLogAreaManager();

public:
	void Recovery(CLRecoverier & recoverier);

public:
	CLLogArea * GetArea();
	void FreeArea(CLLogArea * logArea);

private:
	SLNVMLogAreaPointers * m_pNVMLogAreaPointers;
	std::list<int> m_freeLogAreaArray;
	CLSemaphore m_sem;
	CLMutex m_lock;
};

NS_END
#endif