#include <iostream>
#include "CLPageManager.h"
#include "CLMetaDataManager.h"
#include "CLLargeExtentManager.h"

using namespace std;

CLLargeExtentManager lem;
CLMetaDataManager mdm;

void GetNVM(CLExtent * pExtent)
{
	mdm.AllocANVMBlockForExtent(pExtent);
}

void FreeExtent(CLExtent * pExtent)
{
	mdm.FreeNVMBlockForExtent(pExtent);
	lem.FreeExtent(pExtent,&mdm);
}

int main(int argc, char *argv[])
{
	CLExtent * pExtent1, * pExtent2, * pExtent3;
	pExtent1 = lem.GetAvailableExtent(4096, &mdm);
	pExtent2 = lem.GetAvailableExtent(4096, &mdm);
	pExtent3 = lem.GetAvailableExtent(4096, &mdm);
	GetNVM(pExtent1);
	GetNVM(pExtent2);
	GetNVM(pExtent3);
	FreeExtent(pExtent1);
	FreeExtent(pExtent2);
	FreeExtent(pExtent3);
	return 0;
}