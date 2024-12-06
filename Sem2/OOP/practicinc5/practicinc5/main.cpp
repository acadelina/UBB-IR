#include "practicinc5.h"
#include <QtWidgets/QApplication>
#include"Repo.h"
#include"Serv.h"
#include"GUI.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Repo repo{ "tractoare.txt" };
    Serv serv{ repo };
    GUI gui{ serv };
    gui.show();
    return a.exec();
}
