#pragma once
#include"Observer.h"
#include"Serv.h"
#include"MyModel.h"
#include<QtWidgets>

class Painter :public QWidget
{
public:
	void paintEvent(QPaintEvent* ev)override;
};
class Window :public Observer, public QWidget
{
	Serv& serv;
	string stare;

	MyModel* model;
	QTableView* tabela = new QTableView;
	QWidget* main = new QWidget;
	QVBoxLayout* lymain = new QVBoxLayout;
	QPushButton* btnopen;
	QPushButton* btnclose;
	QPushButton* btnin;

	void init()
	{
		main->setWindowTitle(QString::fromStdString(stare));
		main->setLayout(lymain);
		model = new MyModel(serv.sort(), "");
		tabela->setSelectionMode(QAbstractItemView::SingleSelection);
		tabela->setModel(model);
		lymain->addWidget(tabela);
		btnopen = new QPushButton("Open");
		btnin = new QPushButton("Inprogress");
		btnclose = new QPushButton("Close");
		lymain->addWidget(btnopen);
		lymain->addWidget(btnin);
		lymain->addWidget(btnclose);

	};
	void connect() {
		QObject::connect(btnopen, &QPushButton::clicked, [this] {
			int row = tabela->selectionModel()->selectedIndexes().at(0).row();
			int id = tabela->model()->data(tabela->model()->index(row, 0), Qt::DisplayRole).toInt();
			serv.modificare(id, "open");
			reload();
			});
		QObject::connect(btnin, &QPushButton::clicked, [this] {
			int row = tabela->selectionModel()->selectedIndexes().at(0).row();
			int id = tabela->model()->data(tabela->model()->index(row, 0), Qt::DisplayRole).toInt();
			serv.modificare(id, "inprogress");
			reload();
			});
		QObject::connect(btnclose, &QPushButton::clicked, [this] {
			int row = tabela->selectionModel()->selectedIndexes().at(0).row();
			int id = tabela->model()->data(tabela->model()->index(row, 0), Qt::DisplayRole).toInt();
			serv.modificare(id, "closed");
			reload();
			});
	};
	void reload() {
		model->set_tabel(serv.stari(stare), "");
	};
public:
	Window(Serv& serv, string stare) :serv{ serv }, stare{ stare } {
		serv.addObs(this);
		init();
		connect();
		reload();
	}
	void run()
	{
		main->show();
	}
	void update()override
	{
		model->set_tabel(serv.stari(stare), "");
	}
};

class GUI :public QWidget
{
	Serv& serv;

	MyModel* model;
	QTableView* tabela=new QTableView;
	QLabel* lblid = new QLabel("Id");
	QLabel* lbldesc= new QLabel("descriere");
	QLabel* lblst = new QLabel("stare");
	QLabel* lblprog = new QLabel("prog");

	QLineEdit* edid = new QLineEdit;
	QLineEdit* eddesc = new QLineEdit;
	QLineEdit* edst = new QLineEdit;
	QLineEdit* edprog = new QLineEdit;

	QPushButton* btnadd = new QPushButton("Adaugare");
	

	QLabel* lblcaut = new QLabel("Cautare:");
	QLineEdit* edcaut = new QLineEdit;
	Painter* p;
	void init();
	void connect();
	void load();
	void ferestre();
public:
	GUI(Serv& serv) :serv{ serv } {
		init();
		connect();
		load();
		ferestre();
	}
	void paintEvent(QPaintEvent* ev)override
	{
		QPainter p{ this };
		p.setPen(Qt::darkMagenta);
		p.drawEllipse(QPoint(10, 10), 10, 10);
	}



};