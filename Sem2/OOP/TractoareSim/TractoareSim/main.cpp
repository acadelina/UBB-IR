#include "TractoareSim.h"
#include <QtWidgets/QApplication>
#include"Service.h"
#include"Repo.h"
#include"GUI.h"
#include"Validator.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Repo rep{ "Tractoare.txt" };
    Validator val;
    Serv serv{ rep,val };
    GUI gui{ serv };
    gui.show();
    return a.exec();
}
