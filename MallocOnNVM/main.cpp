#include <iostream>
#include "CLPageManager.h"
#include "CLMetaDataManager.h"
#include "CLSmallExtentManager.h"

using namespace std;

CLSmallExtentManager sem;
CLMetaDataManager mdm;

struct SLPage
{
	void * pAddress;
	unsigned int count;
};
#define  PUT(index) pm.PutPages(sp[index].pAddress, sp[index].count)

int main(int argc, char *argv[])
{
	CLPageManager pm;

	SLPage sp[6];
	sp[0] = { (void *)0x1000, 1 };
	sp[1] = { (void *)0x2000, 1 };
	sp[2] = { (void *)0x3000, 1 };
	sp[3] = { (void *)0x4000, 1 };
	sp[4] = { (void *)0x5000, 1 };
	sp[5] = { (void *)0x6000, 1 };
	PUT(1);
	PUT(2);
	PUT(3);

	return 0;
}