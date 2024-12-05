#pragma once
#include"Serv.h"
#include<QtWidgets>
#include"observer.h"
#include"MyModel.h"

class Window :public Observer, public QWidget
{
	Serv& serv;
	string stare;
	//vector<Task> lista;
	QTableWidget* tabel=new QTableWidget;
	QPushButton* btnopen;
	QPushButton* btnclose;
	QPushButton* btninp;
	QWidget* window = new QWidget;
public:
	Window(Serv& serv, string stare) :serv{ serv }, stare{ stare } {
		this->serv.addObs(this);
		init();
		connect();
		load(serv.stari()[stare]);
	};
	void init()
	{
		
		window->setWindowTitle(QString::fromStdString(stare));
		QVBoxLayout* layout = new QVBoxLayout;
		this->setLayout(layout);
		tabel->setColumnCount(4);
		btnclose = new QPushButton("CLOSE");
		btninp = new QPushButton("INPROGRESS");
		btnopen = new QPushButton("OPEN");
		layout->addWidget(tabel);
		layout->addWidget(btnclose);
		layout->addWidget(btninp);
		layout->addWidget(btnopen);

	}
	void connect()
	{
		QObject::connect(btnclose, &QPushButton::clicked, [this] {
			auto a = tabel->selectedItems()[0]->row();
			auto taskuri = serv.stari()[stare];
			int id = taskuri[a].getid();
			serv.schimbs(id, "closed");
			load(serv.stari()[stare]);
			serv.notify();
			});

		QObject::connect(btnopen, &QPushButton::clicked, [this] {
			auto a = tabel->selectedItems()[0]->row();
			auto taskuri = serv.stari()[stare];
			int id = taskuri[a].getid();
			serv.schimbs(id, "open");
			load(serv.stari()[stare]);
			serv.notify();
			});
		QObject::connect(btninp, &QPushButton::clicked, [this] {
			auto a = tabel->selectedItems()[0]->row();
			auto taskuri = serv.stari()[stare];
			int id = taskuri[a].getid();
			serv.schimbs(id, "inprogress");
			load(serv.stari()[stare]);
			serv.notify();
			});
	}
	void load(vector<Task> t)
	{

		tabel->clear();
		tabel->setRowCount(int(t.size()));
		int n = 0;
		for (auto& i : t)
		{
			tabel->setItem(n, 0, new QTableWidgetItem(QString::number(i.getid())));
			tabel->setItem(n, 1, new QTableWidgetItem(QString::fromStdString(i.getdesc())));
			tabel->setItem(n, 2, new QTableWidgetItem(to_string(i.getprog().size()).c_str()));
			tabel->setItem(n, 3, new QTableWidgetItem(QString::fromStdString(i.getstare())));
			n++;
		}
	}
	void update()override {
		load(serv.stari()[stare]);
	};

};
class GUI :public QWidget,public Observer
{
	Serv& serv;

	//MyModel* model;
	//QTableView* tabela;

	QTableWidget* tabel=new QTableWidget;

	QLineEdit* edid;
	QLineEdit* eddesc;
	QLineEdit* edprg;
	QLineEdit* edstare;

	QLabel* lblid = new QLabel("Id");
	QLabel* lbldesc = new QLabel("Descriere");
	QLabel* lblprog = new QLabel("Programatori");
	QLabel* lblstare = new QLabel("Stare");

	QPushButton* btnadd;
	QLineEdit* edse;
	QLabel* lblse = new QLabel("Search");

	void init();
	void connect();
	void reload(vector<Task> t);
	void windows()
	{
		Window* w1 = new Window(serv, "open");
		Window* w2 = new Window(serv, "closed");
		Window* w3 = new Window(serv, "inprogress");
		w1->show();
		w2->show();
		w3->show();
	}
		;
public:
	explicit GUI(Serv& serv) :serv{ serv } {
		init();
		connect();
		reload(serv.getAll());
		windows();
	}
	virtual void update() override {
		reload(serv.sort());
	}
};