#pragma once
#include"Serv.h"
#include"MyModel.h"
#include<QtWidgets>


class Painter :public QWidget
{
	int nr;
public:
	explicit Painter(int nr) :nr{ nr } {
		this->repaint();

	};
	void paintEvent(QPaintEvent* ev)override;
};

class GUI:public QWidget
{
	Serv& serv;
	string tip;
	int nrRoti;
	MyModel* model;
	QTableView* tabela=new QTableView;

	QLineEdit* edid;
	QLineEdit* eddenum;
	QLineEdit* edtip;
	QLineEdit* edroti;

	QLabel* lblid = new QLabel("Id");
	QLabel* lbldenum = new QLabel("Denumire");
	QLabel* lbltip = new QLabel("Tip");
	QLabel* lblroti = new QLabel("Roti");

	QPushButton* btnadd;
	QComboBox* box;
	Painter* paint;

	void init();
	void load(string tip);
	void connect();
	void dinamicBox();
	void paintEvent(QPaintEvent* ev)override;
public:
	GUI(Serv& serv) :serv{ serv } {
		init();
		connect();
		load("");
		dinamicBox();
	}
};