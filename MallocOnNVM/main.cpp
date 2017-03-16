#include <iostream>
#include <cstdlib>
#include "NVMMalloc.h"

using namespace std;

unsigned int Random(int max)
{
	return rand() % max;
}
//todo CLBlockArea的arenaID的相关设置

int main(int argc, char *argv[])
{
	//void * addr[300];
	//for (int i = 0; i < 300; ++i)
	//{
	//	addr[i] = MallocOnNVM(Random(4096));
	//}
	Recovery();
	return 0;
} 