#ifndef __GLOBAL_BLOCK_AREA_MANAGER_H__
#define __GLOBAL_BLOCK_AREA_MANAGER_H__

#include "CLMutex.h"
#include <list>

class CLBlockArea;
class CLRecoverier;

class CLGlobalBlockAreaManager
{
private:
	CLGlobalBlockAreaManager();
	CLGlobalBlockAreaManager(const CLGlobalBlockAreaManager &);
	CLGlobalBlockAreaManager & operator=(const CLGlobalBlockAreaManager &);

public:
	~CLGlobalBlockAreaManager();

public:
	static CLGlobalBlockAreaManager * GetInstance();

public:
	CLBlockArea * GetABlockArea();
	void FreeBlockArea(CLBlockArea * pArea);
	void FreeBlockAreas(std::list<CLBlockArea *> & areaList, unsigned int freeCount);

public:
	void Recovery(CLRecoverier & recoverier);
	void RecieveFreeBlockAreaRecovery(CLBlockArea * pBlockArea);

private:
	std::list<CLBlockArea *> m_areaList;
	CLBlockArea * m_pFirstBlockArea;
	CLMutex m_lock;
};

#endif