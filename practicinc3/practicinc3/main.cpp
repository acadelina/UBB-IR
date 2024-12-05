#include "practicinc3.h"
#include <QtWidgets/QApplication>
#include"Repo.h"
#include"Serv.h"
#include"GUI.h"
#include"Validator.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Repo rep{ "produse.txt" };
    Validator val;
    Serv serv{ rep,val };
    GUI gui{ serv };
    gui.show();
    return a.exec();
}
