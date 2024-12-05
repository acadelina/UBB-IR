#include "TelefoaneSim.h"
#include <QtWidgets/QApplication>
#include"Repo.h"
#include"Service.h"
#include"GUI.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Repo rep{ "Telefoane.txt" };
    Serv serv{ rep };
    GUI gui{ serv };
    gui.show();
    return a.exec();
}
