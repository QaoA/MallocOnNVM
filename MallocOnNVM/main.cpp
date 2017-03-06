#include <iostream>
#include "CLNVMObject.h"

using namespace std;

int main(int argc, char *argv[])
{
	CLNVMObject * pObject = new CLNVMObject(5);
	delete pObject;
	return 0;
}