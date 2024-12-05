#include"ContarctGUI.h"
#include<iostream>

void ContractGUI::initGUIcmps()
{
	//main
	QVBoxLayout* lyMain = new QVBoxLayout{};
	this->setLayout(lyMain);

	//up
	QWidget* left = new QWidget;
	QHBoxLayout* lyLeft = new QHBoxLayout;
	left->setLayout(lyLeft);

	//add
	QWidget* form1 = new QWidget;
	QFormLayout* lyForm1 = new QFormLayout;
	form1->setLayout(lyForm1);
	aDenumire = new QLabel{ "Denumirea disciplinei:" };
	addDenumire = new QLineEdit;
	
	lyForm1->addRow(aDenumire, addDenumire);
	adauga = new QPushButton("Adauga disciplina");
	lyForm1->addWidget(adauga);
	lyLeft->addWidget(form1);

	//add random
	QWidget* form2 = new QWidget;
	QFormLayout* lyForm2 = new QFormLayout;
	form2->setLayout(lyForm2);
	Number = new QLabel{ "Numarul de discipline:" };
	addNumber = new QLineEdit;
	lyForm2->addRow(Number, addNumber);
	adaugaRandom = new QPushButton("Adauga discipline random");
	lyForm2->addWidget(adaugaRandom);
	lyLeft->addWidget(form2);

	//empty
	gol = new QPushButton("Goleste contract");
	lyLeft->addWidget(gol);

	QWidget* exporto = new QWidget;
	QFormLayout* lye = new QFormLayout;
	exporto->setLayout(lye);
	fisier = new QLabel{ "Fisier: " };
	fis = new QLineEdit;
	lye->addRow(fisier, fis);
	exportcsv = new QPushButton("Export CSV");
	exporthtml = new QPushButton("Export HTML");
	lye->addRow(exportcsv);
	lye->addRow(exporthtml);
	lyLeft->addWidget(exporto);
	paint = new QPushButton("ROnly");
	lyLeft->addWidget(paint);
	

	//down
	QWidget* right = new QWidget;
	QVBoxLayout* lyRight = new QVBoxLayout;
	right->setLayout(lyRight);


	//tabel
	int m = 10;
	int n = 4;
	tabelAT = new QTableWidget(m, n);
	QStringList HeaderList;
	HeaderList << "Denumire" << "Ore" << "Tip" << "Prof";
	tabelAT->setHorizontalHeaderLabels(HeaderList);
	//this->listAT = new QListWidget;*/
	//lista
//	this->listAT = new QListWidget;
	//lyRight->addWidget(listAT);
	lyRight->addWidget(tabelAT);
	//final
	lyMain->addWidget(right);
	lyMain->addWidget(left);

}

void ContractGUI::reloadTable(const vector<Disciplina>& all)
{
	/*listAT->clear();
	for (const auto& a : all)
	{
		QString itemtext = QString::fromStdString(a.getDenum()) + ", " + QString::number(a.getOre()) + ", " + QString::fromStdString(a.getTip()) + ", " + QString::fromStdString(a.getProf());
		QListWidgetItem* item = new QListWidgetItem(itemtext);
		listAT->addItem(item);
	}*/
	tabelAT->clearContents();
	tabelAT->setRowCount(int(all.size()));

	int n = 0;
	for (auto& a : all)
	{
		tabelAT->setItem(n, 0, new QTableWidgetItem(QString::fromStdString(a.getDenum())));
		tabelAT->setItem(n, 1, new QTableWidgetItem(QString::number(a.getOre())));
		tabelAT->setItem(n, 2, new QTableWidgetItem(QString::fromStdString(a.getTip())));
		tabelAT->setItem(n, 3, new QTableWidgetItem(QString::fromStdString(a.getProf())));
		n++;
	}
}

void ContractGUI::connectSignalSlots()
{
	QObject::connect(adauga, &QPushButton::clicked, this, &ContractGUI::add);

	QObject::connect(adaugaRandom, &QPushButton::clicked, this, &ContractGUI::addRandom);

	QObject::connect(gol, &QPushButton::clicked, this, &ContractGUI::empty);

	
	QObject::connect(exportcsv, &QPushButton::clicked, this, &ContractGUI::expCSV);
	QObject::connect(exporthtml, &QPushButton::clicked, this, &ContractGUI::expHTML);
	QObject::connect(paint, &QPushButton::clicked, this, &ContractGUI::paintgui);
	
}

void ContractGUI::add()
{
	try {
		string denum = addDenumire->text().toStdString();
		

		addDenumire->clear();
		
		this->contServ.addToContract(denum);
		
		this->reloadTable(this->contServ.getContract());

		QMessageBox::information(this, "Info", QString::fromStdString("Disciplina adaugata cu succes!"));

	}
	catch (ValidationExceptions& ev)
	{
		QMessageBox::warning(this, "Warning", QString::fromStdString(ev.get_msj()));
	}
	catch (RepositoryExceptions& re)
	{
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.getMsg()));
	}
}

void ContractGUI::addRandom()
{
	int nr = addNumber->text().toInt();
	addNumber->clear();
	this->contServ.fillRandom(nr);
	this->reloadTable(this->contServ.getContract());
}

void ContractGUI::empty()
{
	this->contServ.clearContract();
	this->reloadTable(this->contServ.getContract());
}

void ContractGUI::expCSV()
{
	string fisi = fis->text().toStdString();
	exportToCSV(fisi,contServ.getContract());
	QMessageBox::information(this, "Info", QString::fromStdString("Contract exportat cu succes!"));
}

void ContractGUI::expHTML()
{
	string fisi = fis->text().toStdString();
	exportToHTML(fisi, contServ.getContract());
	QMessageBox::information(this, "Info", QString::fromStdString("Contract exportat cu succes!"));
}

void ContractGUI::paintgui()
{
	//pi->move(10, 10);
	//pi->show();
}