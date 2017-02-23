#include <iostream>
#include "CLMetaDataManager.h"

using namespace std;

CLMetaDataManager m;

int main(int argc, char *argv[])
{
	CLExtent * e;
	for (int i = 0; i < 170; ++i)
	{
		e = m.GetExtent();
		m.AllocANVMBlockForExtent(e);
	}
	e = m.GetExtent();
	m.AllocANVMBlockForExtent(e);
	return 0;
}