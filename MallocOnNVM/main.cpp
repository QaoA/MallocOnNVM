#include <iostream>
#include "CLPageManager.h"
#include "CLMetaDataManager.h"
#include "CLSmallExtentManager.h"

using namespace std;

CLSmallExtentManager sem;
CLMetaDataManager mdm;

void GetNVM(CLExtent * pExtent)
{
	mdm.AllocANVMBlockForExtent(pExtent);
}

void FreeExtent(CLExtent * pExtent)
{
	mdm.FreeNVMBlockForExtent(pExtent);
	sem.FreeExtent(pExtent,&mdm);
}

int main(int argc, char *argv[])
{
	//CLExtent * pExtents[128];
	//for (int i = 0; i < 128; i++)
	//{
	//	pExtents[i] = sem.GetAvailableExtent(31, &mdm);
	//}
	//for (int i = 127; i >= 0; --i)
	//{
	//	sem.FreeExtent(pExtents[i]);
	//}

	CLExtent * p1, *p2;
	p1 = sem.GetAvailableExtent(31, &mdm);
	p2 = sem.GetAvailableExtent(31, &mdm);
	GetNVM(p1);
	GetNVM(p2);
	FreeExtent(p2);
	FreeExtent(p1);
	return 0;
}