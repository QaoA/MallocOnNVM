#include <iostream>
#include <cstdlib>
#include "NVMMalloc.h"

using namespace std;

int main(int argc, char *argv[])
{
	void * p1 = MallocOnNVM(15);
	FreeOnNVM(p1);
	return 0;
}