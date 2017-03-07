#ifndef __GLOBAL_BLOCK_AREA_MANAGER_H__
#define __GLOBAL_BLOCK_AREA_MANAGER_H__

#include "CLMutex.h"

class CLBlockArea;

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
	void DoRecovery();

private:
	CLBlockArea * AppendNewBlockArea();
	void InitFirstBlockArea();
	CLBlockArea * InitABlockArea();

private:
	CLBlockArea * m_pFirstBlockArea;
	CLMutex m_lock;
};

#endif