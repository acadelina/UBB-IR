#pragma once
#include"Serv.h"
#include"MyModel.h"
#include<QtWidgets>

class GUI :public QWidget
{
	Serv& serv;
	MyModel* model;
	QTableView* tabela = new QTableView;

	QLineEdit* edid;
	QLineEdit* eddim;
	QLineEdit* edtabla;
	QLineEdit* edjuc;
	QLineEdit* edstare;

	QLabel* lblid = new QLabel("ID");
	QLabel* lbldim = new QLabel("Dimensiune");
	QLabel* lbltabla = new QLabel("Tabla");
	QLabel* lbljuc = new QLabel("Jucator");
	QLabel* lblstare= new QLabel("stare");

	QPushButton* btnadd;
	QPushButton* btnmod;


	void init();
	void connect();
	void load();

public:
	GUI(Serv& serv) :serv{ serv } {
		init();
		connect();
		load();
	}

};