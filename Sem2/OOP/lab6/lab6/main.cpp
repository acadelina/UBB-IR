#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "repo.h"
#include "service.h"
#include "console.h"
#include"validator.h"

int main()
{
	testDomain();
	testRepo();
	testServ();
	testVal();
	{
		DisRepo repo;
		DisServ serv{ repo };
		DisConsole console{ serv };
		console.start();
	}
	_CrtDumpMemoryLeaks();
}