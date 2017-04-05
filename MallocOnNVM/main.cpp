#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include "NVMMalloc.h"

using namespace std;

unsigned int Random(int max)
{
	return rand() % max;
}

void * ThreadFunc(void *)
{
	void * addr[100];
	for (int i = 0; i < 100; ++i)
	{
		addr[i] = MallocOnNVM(Random(4096));
		NotifyNVMMemoryGet(addr[i]);
	}
	CLLogArea * pLogArea[3];
	for (int i = 0; i < 3; ++i)
	{
		pLogArea[i] = AllocLogArea();
	}
}

void LogRecovery(CLLogArea &)
{
	cout << "recovery" << endl;
}

int main(int argc, char *argv[])
{
	Recovery(LogRecovery);
	//pthread_t t1, t2;
	//pthread_create(&t1, NULL, ThreadFunc, NULL);
	//pthread_create(&t2, NULL, ThreadFunc, NULL);
	//pthread_join(t1, NULL);
	//pthread_join(t2, NULL);
	return 0;
} 