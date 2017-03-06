#include <iostream>
#include <cstdlib>
#include "CLNVMObject.h"

using namespace std;

int Random(int max)
{
	return rand() % max;
}

int main(int argc, char *argv[])
{
	CLNVMObject * array[256];
	for (int i = 0; i < 256; ++i)
	{
		array[i] = new CLNVMObject(Random(4096));
	}
	for (int i = 0; i < 255; ++i)
	{
		delete array[i];
	}
	return 0;
}