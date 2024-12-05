#include "practicinc7.h"
#include <QtWidgets/QApplication>
#include"Repo.h"
#include"Serv.h"
#include"GUI.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Repo rep{ "produs.txt" };
    Serv sev{ rep };
    GUI gui{ sev };
    gui.show();
    return a.exec();
}
