#pragma once
#include"Serv.h"
#include<QtWidgets>

/*class GUI :public QWidget {
	Serv& serv;

	QTableWidget* tabela;

	QLineEdit* edid;
	QLineEdit* edtitlu;
	QLineEdit* edart;
	QLineEdit* edgen;

	QLabel* lblid = new QLabel("Id: ");
	QLabel* lbltitlu = new QLabel("Titlu: ");
	QLabel* lblart = new QLabel("Artist: ");
	QLabel* lblgen = new QLabel("Gen: ");

	QPushButton* btnadd;
	QPushButton* btnrm;

	void init() {
		QHBoxLayout* lymain = new QHBoxLayout;
		this->setLayout(lymain);

		tabela = new QTableWidget(10,7);
		QStringList header;
		header << "Id" << "Titlu" << "Artist" << "Gen" << "Acelasi artist" << "Acelasi gen";
		tabela->setHorizontalHeaderLabels(header);

		lymain->addWidget(tabela);

		QWidget* form1 = new QWidget;
		QFormLayout* lyform1 = new QFormLayout;
		form1->setLayout(lyform1);

		edid = new QLineEdit;
		edgen = new QLineEdit;
		edtitlu = new QLineEdit;
		edart = new QLineEdit;

		lyform1->addRow(lblid, edid);
		lyform1->addRow(lbltitlu, edtitlu);
		lyform1->addRow(lblart, edart);
		lyform1->addRow(lblgen, edgen);

		btnadd = new QPushButton("Adauga");
		btnrm = new QPushButton("Sterge");
		lyform1->addWidget(btnadd);
		lyform1->addWidget(btnrm);

		lymain->addWidget(form1);

	}
	void connect() {
		QObject::connect(btnadd, &QPushButton::clicked,this, &GUI::guiadd);
		QObject::connect(btnrm, &QPushButton::clicked,this, &GUI::guidel);
		QObject::connect(tabela, &QTableWidget::itemSelectionChanged,this, &GUI::select);
	}
	void reload(vector<Melodie> mel) {
		tabela->clearContents();
		tabela->setRowCount(int(mel.size()));
		int n = 0;
		for (auto a : mel)
		{
			tabela->setItem(n, 0,new QTableWidgetItem(QString::number(a.getid())));
			tabela->setItem(n, 1, new QTableWidgetItem(QString::fromStdString(a.gettitlu())));
			tabela->setItem(n, 2, new QTableWidgetItem(QString::fromStdString(a.getartist())));
			tabela->setItem(n, 3, new QTableWidgetItem(QString::fromStdString(a.getgen())));
			int art = serv.nrart(a.getartist());
			int gen = serv.nrgen(a.getgen());
			tabela->setItem(n, 4, new QTableWidgetItem(QString::number(art)));
			tabela->setItem(n, 5, new QTableWidgetItem(QString::number(gen)));
			n++;
		}
	}
public:
	GUI(Serv& serv) :serv{ serv } {
		init();
		connect();
		reload(serv.sort());
	};

	void guiadd() {
		try {
			int id = edid->text().toInt();
			string t = edtitlu->text().toStdString();
			string a = edart->text().toStdString();
			string g = edgen->text().toStdString();
			serv.adauga(id, t, a, g);
			reload(serv.sort());

		}
		catch (RepoExc& re)
		{
			QMessageBox::warning(this, "Warning", QString::fromStdString(re.getmsg()));
		}
	}
	void guidel() {
		try {
			int id = edid->text().toInt();
			
			serv.sterge(id);
			reload(serv.sort());

		}
		catch (RepoExc& re)
		{
			QMessageBox::warning(this, "Warning", QString::fromStdString(re.getmsg()));
		}
	}
	void select() {
		if (tabela->selectedItems().isEmpty())
		{
			return;
		}
		auto selected = tabela->selectedItems();
		
		edid->setText(selected.at(0)->text());
		edtitlu->setText(selected.at(1)->text());
		edart->setText(selected.at(2)->text());
		edgen->setText(selected.at(3)->text());

	}
};*/

class GUI :public QWidget {
	Serv& serv;

	QTableWidget* tabela;

	QLineEdit* edid;
	QLineEdit* edtitlu;
	QLineEdit* edart;
	QLineEdit* edgen;

	QLabel* lblid = new QLabel("ID: ");
	QLabel* lbltitlu = new QLabel("Titlu: ");
	QLabel* lblart = new QLabel("Artist: ");
	QLabel* lblgen = new QLabel("Gen: ");

	QPushButton* btnadd;
	QPushButton* btnrm;
	QPushButton* btnreinc;

	void init() {
		QHBoxLayout* lymain = new QHBoxLayout;
		this->setLayout(lymain);
		QStringList header;
		header<<"Id"<<"Titlu"<<"Artist"<<"Gen" <<"Acelasi art"<<"Acelasi gen";
		tabela = new QTableWidget(10, 6);
		tabela->setHorizontalHeaderLabels(header);

		lymain->addWidget(tabela);

		edid = new QLineEdit;
		edtitlu = new QLineEdit;
		edart = new QLineEdit;
		edgen = new QLineEdit;

		QWidget* form1 = new QWidget;
		QFormLayout* lyform1 = new QFormLayout;
		form1->setLayout(lyform1);

		btnadd = new QPushButton("Adauga");
		btnrm = new QPushButton("Sterge");
		btnreinc = new QPushButton("Reincarca");

		lyform1->addRow(lblid, edid);
		lyform1->addRow(lbltitlu, edtitlu);
		lyform1->addRow(lblart, edart);
		lyform1->addRow(lblgen, edgen);
		lyform1->addWidget(btnadd);
		lyform1->addWidget(btnrm);
		lyform1->addWidget(btnreinc);

		lymain->addWidget(form1);


	}
	void connect() {
		QObject::connect(btnadd, &QPushButton::clicked, this, &GUI::guiadd);
		QObject::connect(btnrm, &QPushButton::clicked, this, &GUI::guirm);
		QObject::connect(btnreinc, &QPushButton::clicked, this, &GUI::guireinc);
		QObject::connect(tabela, &QTableWidget::itemSelectionChanged, this, &GUI::sel);
	}
	void reload(vector<Melodie> mel) {
		tabela->clearContents();
		tabela->setRowCount(int(mel.size()));
		int n = 0;
		for (auto a : mel)
		{
			tabela->setItem(n, 0, new QTableWidgetItem(QString::number(a.getid())));
			tabela->setItem(n, 1, new QTableWidgetItem(QString::fromStdString(a.gettitlu())));
			tabela->setItem(n, 2, new QTableWidgetItem(QString::fromStdString(a.getartist())));
			tabela->setItem(n, 3, new QTableWidgetItem(QString::fromStdString(a.getgen())));
			int nra = serv.nrart(a.getartist());
			int nrg = serv.nrgen(a.getgen());
			tabela->setItem(n, 4, new QTableWidgetItem(QString::number(nra)));
			tabela->setItem(n, 5, new QTableWidgetItem(QString::number(nrg)));
			n++;

		}
	}
public:
	GUI(Serv& serv):serv{serv}{
		init();
		connect();
		reload(serv.sort());
	}
	void guiadd()
	{
		try {
			int id = edid->text().toInt();
			string titlu = edtitlu->text().toStdString();
			string art = edart->text().toStdString();
			string gen = edgen->text().toStdString();
			serv.adauga(id, titlu, art, gen);
			reload(serv.sort());
		}
		catch (RepoExc& re)
		{
			QMessageBox::warning(this, "Warning", QString::fromStdString(re.getmsg()));
		}
	}

	void guirm()
	{

		try {
			int id = edid->text().toInt();
			
			serv.sterge(id);
			reload(serv.sort());
		}
		catch (RepoExc& re)
		{
			QMessageBox::warning(this, "Warning", QString::fromStdString(re.getmsg()));
		}

	}
	void sel()
	{
		auto items = tabela->selectedItems();
		if (items.isEmpty())
			return;
		edid ->setText( items.at(0)->text());
		edtitlu->setText(items.at(1)->text());
		edart->setText(items.at(2)->text());
		edgen->setText(items.at(3)->text());
	}

	void guireinc()
	{
		reload(serv.sort());
	}

};

