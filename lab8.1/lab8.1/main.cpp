#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "repoDis.h"
#include "serviceDis.h"
#include "console.h"
#include "contract.h"
#include "validator.h"

void clearfile()
{
	ofstream f("testFile.txt", ios::trunc);
	f.close();
}
int main()
{
	clearfile();
	testDomain();
	testRepo();
	testServ();
	testContract();
	testValidare();
	testExport();
	testRepoFile();
	testDictRepo();

	{
		cout << "Alege meniu:(1)Repo,(2)Repofisier,(3)RepoDictionar: ";
		int n;
		cin >> n;
		if (n == 1)
		{
			DisRepo repo;
			Validator val;
			DisServ serv{ repo,val };
			DisConsole console{ serv };
			console.start();
		}
		else if (n == 2)
		{
			FileRepo repo{ "Discipline.txt" };
			Validator val;
			DisServ serv{ repo,val };
			DisConsole console{ serv };
			console.start();
		}
		else
		{
			float prob;
			cout << "Dati probabilitate: ";
			cin >> prob;
			DictRepo repo(prob);
			Validator val;
			DisServ serv{ repo,val };
			DisConsole console{ serv };
			console.start();
		}
		
	}
	_CrtDumpMemoryLeaks();
}