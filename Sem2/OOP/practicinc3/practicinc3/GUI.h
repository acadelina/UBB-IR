#pragma once
#include"MyModel.h"
#include"Repo.h"
#include"Validator.h"
#include"Serv.h"
#include<QtWidgets>
#include<QWidget>
#include"observer.h"

class TipuriGUI :public Observer {
private:
	Serv& serv;
	int nr;
	string tip;
	QLabel* lbl = new QLabel;
	QWidget* wid = new QWidget;
	QHBoxLayout* layout = new QHBoxLayout;
public:
	TipuriGUI(Serv& serv, int nr, string tip) :serv{ serv }, nr{ nr }, tip{ tip } {
		this->serv.addObs(this);
		lbl->setText(QString::number(nr));
		wid->setWindowTitle(QString::fromStdString(tip));
		wid->setLayout(layout);
		layout->addWidget(lbl);
	};
	~TipuriGUI()
	{
		this->serv.removeObs(this);
	}
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
	QTableView* tabela = new QTableView;
	MyModel* model = new MyModel{ serv.sortP(),0 };

	QLabel* lblid = new QLabel("ID");
	QLabel* lblnume = new QLabel("Nume");
	QLabel* lbltip = new QLabel("Tip");
	QLabel* lblpret = new QLabel("Pret");

	QLineEdit* edid;
	QLineEdit* ednume;
	QLineEdit* edtip;
	QLineEdit* edpret;

	QPushButton* btnadd;
	QSlider* slide;

	void init();
	void connect();
	void reload();
	void open_dinamic() {
		auto l = serv.tipuri();
		for (auto el : l)
		{
			auto wind = new TipuriGUI{ serv,el.second,el.first };
			wind->run();
		}
	};
		
public:
	GUI(Serv& serv) :serv{ serv } {
		init();
		connect();
		//reload();
		open_dinamic();
	}

};

class Tip:public Observer {
	Serv& serv;
	int nr;
	string ti;
	QLabel* lbl = new QLabel;
	QWidget* wind = new QWidget;
	QHBoxLayout* layout = new QHBoxLayout;
public:
	Tip(Serv &serv,int nr,string ti):serv{serv},nr{nr},ti{ti}{
		this->serv.addObs(this);
		wind->setLayout(layout);
		wind->setWindowTitle(QString::fromStdString(ti));
		lbl->setText(QString::number(nr));
	}
	~Tip()
	{
		this->serv.removeObs(this);
	}
	void update()override
	{
		int n = serv.tipuri()[ti];
		lbl->setText(QString::number(n));
	}
};