#include "Simulare.h"
#include <QtWidgets/QApplication>
#include"GUI.h"

void teste()
{
    testDomain();
    testRepo();
}
int main(int argc, char *argv[])
{
    teste();
    QApplication a(argc, argv);
    Repo rep{ "rochie.txt" };
    Serv serv{ rep };
    GUI gui{ serv };
   gui.show();
    return a.exec();
}
