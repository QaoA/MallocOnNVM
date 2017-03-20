#include <iostream>
#include <cstdlib>
#include "NVMMalloc.h"

using namespace std;

unsigned int Random(int max)
{
	return rand() % max;
}

int main(int argc, char *argv[])
{
	//void * addr[300];
	//for (int i = 0; i < 300; ++i)
	//{
	//	addr[i] = MallocOnNVM(Random(4096));
	//	NotifyNVMMemoryGet(addr[i]);
	//}
	//for (int i = 0; i < 300; ++i)
	//{
	//	if (i & 0x1)
	//	{
	//		NotifyNVMMemoryRelease(addr[i]);
	//		FreeOnNVM(addr[i]);
	//	}
	//}
	//for (int i = 0; i < 300; ++i)
	//{
	//	if (i & 0x1)
	//	{
	//		addr[i] = MallocOnNVM(Random(4096));
	//		NotifyNVMMemoryGet(addr[i]);
	//	}
	//}
	//for (int i = 0; i < 300; ++i)
	//{
	//		NotifyNVMMemoryRelease(addr[i]);
	//		FreeOnNVM(addr[i]);
	//}
	Recovery();
	return 0;
} 