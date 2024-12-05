#include "Melodii2sim.h"
#include <QtWidgets/QApplication>
#include"Repo.h"
#include"Serv.h"
#include"GUI.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Repo rep{ "Melodii.txt" };
    Serv serv{ rep };
    GUI gui{ serv };
    gui.show();
    return a.exec();
}
