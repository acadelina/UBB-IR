#include "practicinc1.h"
#include <QtWidgets/QApplication>
#include "GUI.h"
#include"Serv.h"
#include"Repo.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //testServ();
    Repo repo("melodii.txt");
    Serv serv(repo);
    GUI gui(serv);
    gui.show();
    return a.exec();
}
