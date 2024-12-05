#pragma once
#include<QtWidgets>
#include"Service.h"

class GUI: public QWidget {
	Serv& serv;

	QTableWidget* tabela;
	QLabel* lblModel = new QLabel{ "Model: " };
	QLabel* lblan = new QLabel{ "An: " };
	QLineEdit* edModel;
	QLineEdit* edAn;
	QPushButton* btnmode;
	QPushButton* btnan;
	QPushButton* btnreinc;

	void init() {
		QHBoxLayout* lymain = new QHBoxLayout;
		this->setLayout(lymain);

		QStringList header;
		header << "Tip" << "Model"<<"Culoare" <<"An" << "Pret";
		tabela = new QTableWidget(10, 5);
		tabela->setHorizontalHeaderLabels(header);

		lymain->addWidget(tabela);

		QWidget* form1 = new QWidget;
		QFormLayout* lyform1 = new QFormLayout;
		form1->setLayout(lyform1);

		edAn = new QLineEdit;
		edModel = new QLineEdit;
		lyform1->addRow(lblModel, edModel);
		lyform1->addRow(lblan, edAn);
		btnmode = new QPushButton("Filtrare model");
		btnan = new QPushButton("Filtrare An");
		btnreinc = new QPushButton("Reincarca");
		lyform1->addWidget(btnmode);
		lyform1->addWidget(btnan);
		lyform1->addWidget(btnreinc);
		lymain->addWidget(form1);
	}
	void connect()
	{
		QObject::connect(tabela, &QTableWidget::itemSelectionChanged, this, &GUI::guisel);
		QObject::connect(btnan, &QPushButton::clicked, this, &GUI::guifilta);
		QObject::connect(btnmode, &QPushButton::clicked, this, &GUI::guifiltm);
		QObject::connect(btnreinc, &QPushButton::clicked, this, &GUI::guireinc);
	}
	void reload(vector<Telefon> t) {
		tabela->clearContents();
		tabela->setRowCount(int(t.size()));
		int n = 0;
		for (auto a : t)
		{
			tabela->setItem(n, 0, new QTableWidgetItem(QString::fromStdString(a.gettip())));
			tabela->setItem(n, 1, new QTableWidgetItem(QString::fromStdString(a.getmodel())));
			tabela->setItem(n, 2, new QTableWidgetItem(QString::fromStdString(a.getculoare())));
			tabela->setItem(n, 3, new QTableWidgetItem(QString::number(a.getan())));
			tabela->setItem(n, 4, new QTableWidgetItem(QString::number(a.getpret())));
			n++;
		}
	}
public:
	GUI(Serv& serv) :serv{ serv } {
		init();
		connect();
		reload(serv.getL());
	}
	void guifiltm() {
		string mod = edModel->text().toStdString();
		reload(serv.filtm(mod));
	}
	void guifilta()
	{
		int an = edAn->text().toInt();
		reload(serv.filta(an));
	}
	void guireinc() {
		reload(serv.getL());
	}
	void guisel()
	{

		if (tabela->selectedItems().isEmpty()) {
			return;
		}
		auto selectedItem = tabela->selectedItems();
		int an = selectedItem.at(3)->text().toInt();
		string model = selectedItem.at(1)->text().toStdString();
		//Telefon phone = selectedItem->data(Qt::UserRole).value<Telefon>();
		
		edAn->setText(QString::number(an));
		edModel->setText(QString::fromStdString(model));
	}
};