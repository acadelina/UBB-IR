#include "lab100.h"
#include <QtWidgets/QApplication>
#include <stdlib.h>
#include <crtdbg.h>
#include "repoDis.h"
#include "serviceDis.h"
#include "Export.h"
#include "contract.h"
#include "validator.h"
#include "DisciplinaGUI.h"

void clearfile()
{
    ofstream f("testFile.txt", ios::trunc);
    f.close();
}
void test() {
	
	clearfile();
	testDomain();
	testRepo();
	testServ();
	testContract();
	testValidare();
	testExport();
	testRepoFile();
	testDictRepo();
}
int main(int argc, char *argv[])
{
	test();
	
	{
		QApplication a(argc, argv);

		FileRepo repo{ "Discipline.txt" };
		Validator val;
		DisServ serv{ repo,val };
		DisciplinaGUI gui{ serv };
		gui.setWindowState(Qt::WindowMaximized);
		gui.show();
		return a.exec();
	}
	//return 0;
}
