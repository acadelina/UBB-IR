#pragma once
#include"Serv.h"
#include"Observer.h"
#include<QtWidgets>

class Window :public Observer,public QWidget
{
	Serv& serv;
	string stare;
	/*
	initializez tot ce vreau sa pun pe fereastra
	*/
	QTableWidget* tabel=new QTableWidget;
	QWidget* wid = new QWidget;
	QVBoxLayout* ly = new QVBoxLayout;
	QPushButton* btnopen = new QPushButton("open");
	QPushButton* btninp = new QPushButton("inprogress");
	QPushButton* btnclose = new QPushButton("closed");

	//functie de init
	void init();
	//functie de load
	void load();
	//functie de connect
	void connect();
public:
	//constructorul clasei window
	Window(Serv& serv, string stare) :serv{ serv }, stare{ stare } {
		serv.addObs(this);
		init();
		connect();
		load();

	}
	//functia de update
	void update()override {
		load();
	}
	//functia de run
	void run()
	{
		wid->show();
	}
	//destructorul
	~Window()
	{
		serv.rmObs(this);
	}

};

class GUI :public QWidget
{
	Serv& serv;
	//initializez componenetele ferestrei mari
	QTableWidget* tabel=new QTableWidget;
	QLineEdit* edid = new QLineEdit;
	QLineEdit* eddesc = new QLineEdit;
	QLineEdit* edstare = new QLineEdit;
	QLineEdit* edprog = new QLineEdit;

	QLabel* lblid = new QLabel("ID");
	QLabel* lbldesc = new QLabel("Descriere");
	QLabel* lblstare = new QLabel("Stare");
	QLabel* lblprog = new QLabel("Proarmatori");

	QLabel* lblcaut = new QLabel("Search");
	QLineEdit* edcaut = new QLineEdit;
	QPushButton* btnadd = new QPushButton("Adaugare");

	//initializare
	void init();
	//incarcare date in tabel
	void load(vector<Task> v);
	//conectare
	void connect();
	//creare ferestre
	void windows();

public:
	GUI(Serv& serv) :serv{ serv } {
		init();
		connect();
		load(serv.getAll());
		windows();
	}
};