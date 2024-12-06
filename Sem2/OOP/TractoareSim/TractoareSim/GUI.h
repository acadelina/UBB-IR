#pragma once
#include<qwidget.h>
#include<QtWidgets>
#include<QtWidgets/QApplication>
#include"Service.h"

class GUI :public QWidget {
private:
	Serv& serv;

	QTableWidget* tabela;

	QLabel* lblid = new QLabel{ "Id: " };
	QLabel* lbldenum = new QLabel{ "Denumire: " };
	QLabel* lbltip = new QLabel{ "Tip: " };
	QLabel* lblroti = new QLabel{ "Roti: " };

	QLineEdit* edid;
	QLineEdit* eddenum;
	QLineEdit* edtip;
	QLineEdit* edroti;

	QPushButton* btnadd;
	QPushButton* filt;

	void initGUI();
	void reload(vector<Tractor> tr);
	void connect();
public:
	GUI(Serv& serv) :serv{ serv } {
		initGUI();
		connect();
		reload(serv.sort());
	}
	void guiadd();
	void guifiltr();



};