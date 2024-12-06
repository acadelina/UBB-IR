#include"GUI.h"

void PGUI::initGUI()
{
	QHBoxLayout* lymain = new QHBoxLayout{};
	this->setLayout(lymain);

	QWidget* left = new QWidget;
	QVBoxLayout* lyleft = new QVBoxLayout;
	left->setLayout(lyleft);
	tabela = new QTableWidget(10, 5);
	QStringList header;
	header << "Id" << "Nume" << "Tip" << "Pret" << "Producator";
	tabela->setHorizontalHeaderLabels(header);
	lyleft->addWidget(tabela);

	QWidget* right = new QWidget;
	QVBoxLayout* lyright = new QVBoxLayout;
	right->setLayout(lyright);

	QWidget* form1 = new QWidget;
	QFormLayout* lyform1 = new QFormLayout;
	form1->setLayout(lyform1);
	Ednume = new QLineEdit;
	Edid = new QLineEdit;
	Edtip = new QLineEdit;
	Edpret = new QLineEdit;
	Edprod = new QLineEdit;
	lyform1->addRow(id, Edid);
	lyform1->addRow(nume, Ednume);
	lyform1->addRow(tip, Edtip);
	lyform1->addRow(pret, Edpret);
	lyform1->addRow(producator, Edprod);
	btnAdd = new QPushButton("Adauga produs");
	btnrm = new QPushButton("Sterge produs");
	btnmod = new QPushButton("Modifica produs");
	btnsortN = new QPushButton("Sorteaza dupa nume");
	btnsortP = new QPushButton("Sorteaza dupa pret");
	btnfiltN = new QPushButton("Filtreaza dupa nume");
	btnfiltP = new QPushButton("Filtreaza dupa pret");
	lyform1->addWidget(btnAdd);
	lyform1->addWidget(btnrm);
	lyform1->addWidget(btnmod);
	lyform1->addWidget(btnfiltN);
	lyform1->addWidget(btnfiltP);
	lyform1->addWidget(btnsortN);
	lyform1->addWidget(btnsortP);

	//desc = new QCheckBox;
	lyform1->addRow(labeldesc, desc);
	lyright->addWidget(form1);
	lymain->addWidget(left);
	lymain->addWidget(right);
}

void PGUI::reloadList(const std::vector<Produs> all)
{
	tabela->clearContents();
	tabela->setRowCount(int(all.size()));

	int n = 0;
	for (auto& a : all)
	{
		tabela->setItem(n, 0, new QTableWidgetItem(QString::number(a.getId())));
		tabela->setItem(n, 1, new QTableWidgetItem(QString::fromStdString(a.getNume())));
		tabela->setItem(n, 2, new QTableWidgetItem(QString::fromStdString(a.getTip())));
		tabela->setItem(n, 3, new QTableWidgetItem(QString::number(a.getPret())));
		tabela->setItem(n, 4, new QTableWidgetItem(QString::fromStdString(a.getProd())));
		n++;
	}
}

void PGUI::connectSignalSlots()
{
	QObject::connect(btnAdd, &QPushButton::clicked, this, &PGUI::guiadd);
	QObject::connect(btnrm, &QPushButton::clicked, this, &PGUI::guidelete);
	QObject::connect(btnmod, &QPushButton::clicked, this, &PGUI::guimod);
	QObject::connect(btnsortN, &QPushButton::clicked, this, &PGUI::guisortN);
	QObject::connect(desc, &QCheckBox::stateChanged, this, &PGUI::sortOrderCh);
}

void PGUI::guiadd()
{
	try
	{
		int id = Edid->text().toInt();
		string d = Ednume->text().toStdString();
		string t = Edtip->text().toStdString();
		int p = Edpret->text().toInt();
		string pro = Edprod->text().toStdString();

		Edid->clear();
		Ednume->clear();
		Edtip->clear();
		Edpret->clear();
		Edprod->clear();

		this->serv.adaugare(id, d, t, p, pro);
		this->reloadList(this->serv.getList());
	}
	catch (ValidationExceptions& ev)
	{
		QMessageBox::warning(this, "Warning", QString::fromStdString(ev.get_msj()));
	}
	catch (RepoExceptions& er)
	{
		QMessageBox::warning(this, "Warning", QString::fromStdString(er.getMsg()));
	}
}

void PGUI::guidelete()
{
	try
	{
		int id = Edid->text().toInt();
		string d = Ednume->text().toStdString();
		string t = Edtip->text().toStdString();
		int p = Edpret->text().toInt();
		string pro = Edprod->text().toStdString();

		Edid->clear();
		Ednume->clear();
		Edtip->clear();
		Edpret->clear();
		Edprod->clear();

		this->serv.stergere(id, d, t, p, pro);
		this->reloadList(this->serv.getList());
	}
	catch (ValidationExceptions& ev)
	{
		QMessageBox::warning(this, "Warning", QString::fromStdString(ev.get_msj()));
	}
	catch (RepoExceptions& er)
	{
		QMessageBox::warning(this, "Warning", QString::fromStdString(er.getMsg()));
	}
}

void PGUI::guimod()
{
	try
	{
		int id = Edid->text().toInt();
		string d = Ednume->text().toStdString();
		string t = Edtip->text().toStdString();
		int p = Edpret->text().toInt();
		string pro = Edprod->text().toStdString();

		Edid->clear();
		Ednume->clear();
		Edtip->clear();
		Edpret->clear();
		Edprod->clear();

		this->serv.modificare(id, d, t, p, pro);
		this->reloadList(this->serv.getList());
	}
	catch (ValidationExceptions& ev)
	{
		QMessageBox::warning(this, "Warning", QString::fromStdString(ev.get_msj()));
	}
	catch (RepoExceptions& er)
	{
		QMessageBox::warning(this, "Warning", QString::fromStdString(er.getMsg()));
	}
}

void PGUI::guisortN()
{

	//string d = Ednume->text().toStdString();
	//Ednume->clear();
	this->reloadList(serv.sortareNume(ord));
}

void PGUI::sortOrderCh(int state)
{
	if (state==Qt::Checked)
		ord = 1;
	else
		ord = 0;
}