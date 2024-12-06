#include "practicinc2.h"
#include <QtWidgets/QApplication>
#include"Domain.h"
#include"Repo.h"
#include"Serv.h"
#include"GUI.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Repo rep{ "melodii.txt" };
    Serv serv{ rep };
    GUI gui{ serv };
    gui.show();
    return a.exec();
}
