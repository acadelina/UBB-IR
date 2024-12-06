#include "Melodii1Sim.h"
#include"GUI.h"
#include"Service.h"
#include"Repo.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FileRepo repo{ "Produse.txt" };
    Validator val;
    Serv serv{ repo,val };
    PGUI gui{ serv };
    gui.show();
   // w.show();
    return a.exec();
}
