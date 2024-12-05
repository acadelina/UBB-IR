#include "Practic.h"
#include <QtWidgets/QApplication>
#include"repoo.h"
#include"Serv.h"
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
    Repo rep{ "task.txt" };
    Serv serv{ rep };
    GUI gui{ serv };
    
    gui.show();
    return a.exec();
}
