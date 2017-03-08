#include <iostream>
#include <cstdlib>
#include "NVMMalloc.h"

using namespace std;

int main(int argc, char *argv[])
{
	//CLMetadataManager->GetExtent() ·ÏÆú

	void * p1 = MallocOnNVM(15);
	FreeOnNVM(p1);
	return 0;
}