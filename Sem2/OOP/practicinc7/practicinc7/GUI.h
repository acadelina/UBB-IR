#pragma once
#include"Observer.h"
#include"MyModel.h"
#include"Serv.h"
#include<QtWidgets>

class Window :public QWidget, public Observer
{
	Serv& serv;
	string tip;
	int nr;
	QWidget* wid=new QWidget;
	QVBoxLayout* ly = new QVBoxLayout;
	QLabel* lbl=new QLabel;
	
	
public:
	Window(Serv& serv, string tip, int nr) :serv{ serv }, tip{ tip }, nr{ nr } {
		this->serv.addobs(this);
		
		wid->setLayout(ly);
		wid->setWindowTitle(QString::fromStdString(tip));
		nr = serv.tipuri().at(tip);
		lbl->setText(QString::number(nr));
		ly->addWidget(lbl);
		//wid->show();

	};
	void update()override
	{
		nr = serv.tipuri()[tip];
		lbl->setText(QString::number(nr));
	}
	void run()
	{
		wid->show();
	}

};

class GUI :public QWidget
{
	Serv& serv;
	MyModel* model;
	QTableView* tabela = new QTableView;
	int pret;

	QLineEdit* edid;
	QLineEdit* ednum;
	QLineEdit* edtip;
	QLineEdit* edpret;

	QLabel* lblid = new QLabel("ID");
	QLabel* lblnum = new QLabel("Nume");
	QLabel* lbltip = new QLabel("Tip");
	QLabel* lblpret = new QLabel("Pret");

	QPushButton* btnadd;
	QSlider* slide = new QSlider;
	
	void init();
	void load();
	void connect();
	void dinamicwind();
public:
	GUI(Serv& serv) :serv{ serv } {
		init();
		connect();
		//load();
		dinamicwind();
	}

};