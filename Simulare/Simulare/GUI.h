#pragma once
#include"Serv.h"
#include<sstream>
#include<QtWidgets>

class GUI :public QWidget {
	Serv& serv;

	//lista
	QListWidget* lista;

	//butoanele
	QPushButton* btninc;
	QPushButton* btnsortm;
	QPushButton* btnsortp;
	QPushButton* btnsortn;

	//etichetele
	//QLabel* lblcod=new QLabel("Cod");
	QLabel* lbldenum= new QLabel("Denumire:");
	QLabel* lblmarime= new QLabel("Marime:");
	QLabel* lblpret=new QLabel("Pret:");
	//QLabel* lbldisp=new QLabel("Disp:");

	
	//QLineEdit* edcod;
	QLineEdit* eddeum;
	QLineEdit* edmarime;
	QLineEdit* edpret;
	//QLineEdit* eddis;
	
	//functie de initializare
	void init() {
		QHBoxLayout* lymain = new QHBoxLayout;
		this->setLayout(lymain);
		lista = new QListWidget;
		lymain->addWidget(lista);

		//edcod = new QLineEdit;
		eddeum = new QLineEdit;
		edmarime = new QLineEdit;
		edpret = new QLineEdit;
		//eddis = new QLineEdit;

		QWidget* form1 = new QWidget;
		QFormLayout* lyf = new QFormLayout;
		form1->setLayout(lyf);

		//lyf->addRow(lblcod, edcod);
		lyf->addRow(lbldenum, eddeum);
		lyf->addRow(lblmarime, edmarime);
		lyf->addRow(lblpret, edpret);
		//lyf->addRow(lbldisp, eddis);

		btninc = new QPushButton("Inchiriaza");
		btnsortm = new QPushButton("Sorteaza dupa marime");
		btnsortn = new QPushButton("Nesortat");
		btnsortp = new QPushButton("Sorteaza dupa pret");

		lyf->addWidget(btninc);
		lyf->addWidget(btnsortm);
		lyf->addWidget(btnsortn);
		lyf->addWidget(btnsortp);

		lymain->addWidget(form1);



	}
	//functie de conectare
	void conect()
	{
		QObject::connect(btninc, &QPushButton::clicked, this, &GUI::guiinc);
		QObject::connect(btnsortp, &QPushButton::clicked, this, &GUI::guisortp);
		QObject::connect(btnsortm, &QPushButton::clicked, this, &GUI::guisortm);
		QObject::connect(btnsortn, &QPushButton::clicked, this, &GUI::guinesort);
		QObject::connect(lista, &QListWidget::itemSelectionChanged, this, &GUI::sel);
	}
	//functie de incarcare a listei
	void reload(vector<Rochie> r)
	{
		lista->clear();
		//int n = 0;
		for (auto a : r)
		{
			QString p = QString::fromStdString(a.getdenum()) + ',' + QString::fromStdString(a.getmarime()) + ',' + QString::number(a.getpret());
			
			lista->addItem(new QListWidgetItem(p));
			
		}
	}
public:
	GUI(Serv& serv) :serv{ serv } {
		init();
		conect();
		reload(serv.getL());
	}
	void guiinc()
	{
		try {
			///int cod = edcod->text().toInt();
			string d = eddeum->text().toStdString();
			string m = edmarime->text().toStdString();
			int pret = edpret->text().toInt();
			//string inc = eddis->text().toStdString();
			//bool disp;
			//if (inc == "True")
				//disp = true;
			//else
				//disp = false;
			serv.Inchiriere( d, m, pret);
		}
		catch (ServExc& se)
		{
			QMessageBox::warning(this, "Warning", QString::fromStdString(se.getmsj()));
		}
		

	}

	void guinesort()
	{
		reload(serv.getL());
	}

	void guisortm()
	{
		reload(serv.sortM());
	}

	void guisortp()
	{
		reload(serv.sortp());
	}

	void sel()
	{
		
		auto selected = lista->selectedItems();
		if (selected.isEmpty())
			return;
		auto ss = stringstream((selected.at(0)->text().toStdString()));
		vector<string> arg;
		string a;
		while (getline(ss, a, ','))
		{
			arg.push_back(a);
		}
		eddeum->setText(QString::fromStdString(arg[0]));
		
		edmarime->setText(QString::fromStdString(arg[1]));
		edpret->setText(QString::fromStdString(arg[2]));
	}

};