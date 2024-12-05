#include "practicinc8.h"
#include <QtWidgets/QApplication>
#include"Serv.h"
#include"Repo.h"
#include"Domain.h"
#include"GUI.h"

void test()
{
    testDomain();
    testRepo();
    testServ();
}
int main(int argc, char *argv[])
{
    //test();
    QApplication a(argc, argv);
    Repo rep{ "mel.txt" };
    Serv serv{ rep };
    GUI gui{ serv };
    gui.show();
    return a.exec();
}
