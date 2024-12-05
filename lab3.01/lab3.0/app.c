//#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC
#include<stdlib.h>
#include<crtdbg.h>
#include"ui.h"

int main()
{
	teste();
	run();
	_CrtDumpMemoryLeaks();
}