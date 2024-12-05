
#include<QtWidgets/QHBoxLayout>
#include<QtWidgets/QTableWidget>
#include<QtWidgets/QHeaderView>
#include<qformlayout.h>
#include<QtWidgets/QWidget>
#include<QCheckBox>
#include<QStandardItemModel>
#include"DisciplinaGUI.h"
//#include"contractGUI.h"
//#include"contRoGUI.h"

void DisciplinaGUI::initGUI()
{
	//QWidget* fereastra_1 = new QWidget;
	//main layout
	QHBoxLayout* lyMain = new QHBoxLayout{};
	this->setLayout(lyMain);

	//left part
	QWidget* left = new QWidget;
	QVBoxLayout* lyleft = new QVBoxLayout;
	left->setLayout(lyleft);

	QWidget* form0 = new QWidget;
	QFormLayout* lyform0 = new QFormLayout;
	form0->setLayout(lyform0);
	btncont = new QPushButton("Schimba pe CRUD");
	btnRo = new QPushButton("Schimba pe ReadOnly");
	lyform0->addWidget(btncont);
	lyform0->addWidget(btnRo);
	lyleft->addWidget(form0);
	//add
	QWidget* form1 = new QWidget;
	QFormLayout* lyform1 = new QFormLayout;
	form1->setLayout(lyform1);
	addDenum = new QLineEdit;
	addOre = new QLineEdit;
	addTip = new QLineEdit;
	addProf = new QLineEdit;
	lyform1->addRow(adenum, addDenum);
	lyform1->addRow(aore, addOre);
	lyform1->addRow(atip, addTip);
	lyform1->addRow(aprof, addProf);
	btnAdd = new QPushButton("Adauga disciplina");
	lyform1->addWidget(btnAdd);
	lyleft->addWidget(form1);

	//sterge
	QWidget* form2 = new QWidget;
	QFormLayout* lyForm2 = new QFormLayout;
	form2->setLayout(lyForm2);

	denumDel = new QLineEdit;
	lyForm2->addRow(denumD, denumDel);
	btnsterge = new QPushButton("Sterge disciplina");
	lyForm2->addWidget(btnsterge);
	lyleft->addWidget(form2);

	//modifica
	QWidget* form3 = new QWidget;
	QFormLayout* lyForm3 = new QFormLayout;
	form3->setLayout(lyForm3);

	modDenum = new QLineEdit;
	modOre = new QLineEdit;
	modTip = new QLineEdit;
	modProf = new QLineEdit;
	lyForm3->addRow(mdenum, modDenum);
	lyForm3->addRow(more, modOre);
	lyForm3->addRow(mtip, modTip);
	lyForm3->addRow(mprof, modProf);
	btnmodif = new QPushButton("Modifica Disciplina");
	lyForm3->addWidget(btnmodif);
	lyleft->addWidget(form3);

	//sortare
	QWidget* form4 = new QWidget;
	QVBoxLayout* lyv4 = new QVBoxLayout;
	QWidget* lyh4 = new QWidget;
	QHBoxLayout* lyForm4 = new QHBoxLayout;
	QWidget* lyhord4 = new QWidget;
	QHBoxLayout* lyord4 = new QHBoxLayout;
	lyhord4->setLayout(lyord4);
	lyord4->addWidget(labeldesc);
	lyord4->addWidget(desc);
	form4->setLayout(lyv4);
	lyh4->setLayout(lyForm4);
	btnSortByDenum = new QPushButton("Sortare dupa denumire");
	btnSortByOre = new QPushButton("Sortare dupa ore");
	btnSortByPT = new QPushButton("Sortare dupa tip si prof");
	lyv4->addWidget(labelsort);
	lyv4->addWidget(lyhord4);
	lyForm4->addWidget(btnSortByDenum);
	lyForm4->addWidget(btnSortByOre);
	lyForm4->addWidget(btnSortByPT);
	lyv4->addWidget(lyh4);
	lyleft->addWidget(form4);

	//filtrare
	QWidget* form5 = new QWidget;
	QFormLayout* lyform5 = new QFormLayout;
	form5->setLayout(lyform5);
	fOre = new QLineEdit();
	btnfiltrore = new QPushButton("Filtreaza");
	fProf = new QLineEdit();
	btnfiltrprof = new QPushButton("Filtreaza");
	lyform5->addRow(filtrOre, fOre);
	lyform5->addWidget(btnfiltrore);
	lyform5->addRow(filtrProf, fProf);
	lyform5->addWidget(btnfiltrprof);
	lyleft->addWidget(form5);

	//contract
	//btnCont = new QPushButton("ContractCRUD");
	//btncrud = new QPushButton("ContractRO");
	//lyleft->addWidget(btnCont);
	//lyleft->addWidget(btncrud);
	
	QWidget* right = new QWidget;
	QHBoxLayout* lyright = new QHBoxLayout;
	right->setLayout(lyright);

	//int m = 10;
	//int n = 4;
	table = new QTableView();
	model = new disListModel(table);
	table->setModel(model);
	//QStringList HeaderList;
	//HeaderList << "Denumire" << "Ore" << "Tip" << "Prof";
	//table->setHorizontalHeaderLabels(HeaderList);
	lyright->addWidget(table);

	//this->table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	//undo
	undo = new QPushButton("UNDO");
	lyright->addWidget(undo);

	QWidget* tipuri = new QWidget;
	QVBoxLayout* lytipuri = new QVBoxLayout;
	tipuri->setLayout(lytipuri);
	map rep = serv.raport();
	if (rep["real"] > 0)
	{
		tip1 = new QPushButton("real");
		lytipuri->addWidget(tip1);
	}
	if (rep["uman"] > 0)
	{
		tip2 = new QPushButton("uman");
		lytipuri->addWidget(tip2);
	}
	if (rep["altele"] > 0)
	{
		tip3 = new QPushButton("altele"); 
		lytipuri->addWidget(tip3);
	}
	lyright->addWidget(tipuri);
	
	
	lyMain->addWidget(left);
	lyMain->addWidget(right);

	QWidget* wid = new QWidget;
	QVBoxLayout* layout = new QVBoxLayout;
	wid->setLayout(layout);
	
	populateCont = new QPushButton("Populeaza contract");
	populate = new QLineEdit();
	addCont = new QPushButton("Adauga disciplina in contract");
	addC = new QLineEdit();
	emptyCont = new QPushButton("Goleste contract");
	layout->addWidget(populate);
	layout->addWidget(populateCont);
	layout->addWidget(labelCAdd);
	layout->addWidget(addC);
	layout->addWidget(addCont);
	layout->addWidget(emptyCont);
	lyMain->addWidget(wid);
	
}

void clearLayout(QLayout* layout)
{
	if (layout == NULL)
		return;
	QLayoutItem* item;
	while ((item = layout->takeAt(0))) {
		if (item->layout()) {
			clearLayout(item->layout());
			delete item->layout();
		}
		if (item->widget()) {
			delete item->widget();
		}
		delete item;
	}
}

void DisciplinaGUI::addbtns()
{
	return;
}

void DisciplinaGUI::reloadList(const std::vector<Disciplina> all)
{
	//his->table->viewport()->update();
	/*table->clearContents();
	table->setRowCount(int(all.size()));

	int n = 0;
	for (auto& a : all)
	{
		table->setItem(n, 0, new QTableWidgetItem(QString::fromStdString(a.getDenum())));
		table->setItem(n, 1, new QTableWidgetItem(QString::number(a.getOre())));
		table->setItem(n, 2, new QTableWidgetItem(QString::fromStdString(a.getTip())));
		table->setItem(n, 3, new QTableWidgetItem(QString::fromStdString(a.getProf())));
		n++;
	}*/
	model->setList(all);
}

void DisciplinaGUI::connectSignalSlots()
{
	QObject::connect(btnAdd, &QPushButton::clicked, this, &DisciplinaGUI::guiadd);

	QObject::connect(btnsterge, &QPushButton::clicked, this, &DisciplinaGUI::guidelete);

	QObject::connect(btnmodif, &QPushButton::clicked, this, &DisciplinaGUI::guimod);

	QObject::connect(btnSortByDenum, &QPushButton::clicked, this, &DisciplinaGUI::guisortbydenum);

	QObject::connect(btnSortByOre, &QPushButton::clicked, this, &DisciplinaGUI::guisortbyore);

	QObject::connect(btnSortByPT, &QPushButton::clicked, this, &DisciplinaGUI::guisortbyPT);

	QObject::connect(desc, &QCheckBox::stateChanged, this, &DisciplinaGUI::sortOrderChanged);

	QObject::connect(btnfiltrore, &QPushButton::clicked, [&]() {
		int ore = this->fOre->text().toInt();
		fOre->clear();
		this->reloadList(serv.filtrareOre(ore));
		});
	QObject::connect(btnfiltrprof, &QPushButton::clicked, [&]() {
		string prof = this->fProf->text().toStdString();
		fProf->clear();
		this->reloadList(serv.filtrareCD(prof));
		});

	QObject::connect(undo, &QPushButton::clicked,this, &DisciplinaGUI::guiundo);

	QObject::connect(tip1, &QPushButton::clicked, this, &DisciplinaGUI::realgui);

	QObject::connect(tip2, &QPushButton::clicked, this, &DisciplinaGUI::umangui);

	QObject::connect(tip3, &QPushButton::clicked, this, &DisciplinaGUI::altelegui);

	QObject::connect(btncont, &QPushButton::clicked, this, &DisciplinaGUI::guicontract);

	QObject::connect(btnRo, &QPushButton::clicked, this, &DisciplinaGUI::guicrud);

	QObject::connect(addCont, &QPushButton::clicked, this, &DisciplinaGUI::guiaddCont);

	QObject::connect(emptyCont, &QPushButton::clicked, this, &DisciplinaGUI::guiemptyCont);

	QObject::connect(populateCont, &QPushButton::clicked, this, &DisciplinaGUI::guipopulateCont);



}

void DisciplinaGUI::guiadd()
{
	try {
		string denum = addDenum->text().toStdString();
		int ore = addOre->text().toInt();
		string tip = addTip->text().toStdString();
		string prof = addProf->text().toStdString();

		addDenum->clear();
		addOre->clear();
		addTip->clear();
		addProf->clear();

		this->serv.addDis(denum, ore, tip, prof);
		//this->addbtns();
		this->reloadList(this->serv.getDList());

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

void DisciplinaGUI::guidelete()
{
	try {
		string denum = denumDel->text().toStdString();
		denumDel->clear();
		this->serv.removeDis(denum);
		this->reloadList(serv.getDList());

		QMessageBox::information(this, "Info", QString::fromStdString("Disciplina stearsa cu succes!"));
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

void DisciplinaGUI::guimod()
{
	try {
		string denum = modDenum->text().toStdString();
		int ore = modOre->text().toInt();
		string tip = modTip->text().toStdString();
		string prof = modProf->text().toStdString();

		modDenum->clear();
		modOre->clear();
		modTip->clear();
		modProf->clear();

		this->serv.modifyDis(denum, ore, tip, prof);
		
		this->reloadList(this->serv.getDList());

		QMessageBox::information(this, "Info", QString::fromStdString("Disciplina modificata cu succes!"));

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

void DisciplinaGUI::guisortbydenum()
{
	this->reloadList(serv.sortByDenum(ord));

}

void DisciplinaGUI::guisortbyore()
{
	this->reloadList(serv.sortByOre(ord));
}

void DisciplinaGUI::guisortbyPT()
{
	this->reloadList(serv.sortByPT(ord));
}

void DisciplinaGUI::sortOrderChanged(int state) {
	if (state == Qt::Checked)
	{
		ord = 1;
	}
	else
		ord = 0;
	
}

void DisciplinaGUI::guiundo() {
	try {
		serv.undo();
		reloadList(serv.getDList());
		QMessageBox::information(this, "Info", QString::fromStdString("Undo realizat cu succes!"));
	}
	catch (RepositoryExceptions& re)
	{
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.getMsg()));
	}
}

void DisciplinaGUI::realgui()
{
	map report = serv.raport();
	int nr = report["real"];
	QMessageBox::information(this, "Numar", QString::number(nr));
}

void DisciplinaGUI::umangui()
{
	map report = serv.raport();
	int nr = report["uman"];
	QMessageBox::information(this, "Numar", QString::number(nr));
}

void DisciplinaGUI::altelegui()
{
	map report = serv.raport();
	int nr = report["altele"];
	QMessageBox::information(this, "Numar", QString::number(nr));
}

void DisciplinaGUI::guicontract()
{
	contCRUDGUI* c = new contCRUDGUI(serv);
	c->setAttribute(Qt::WA_DeleteOnClose);
	c->initcontGUI();
	c->connectSignalSlots();
	c->reloadList(serv.getContract());
	c->show();
	
	cont->service.addObserver(c);

}

void DisciplinaGUI::guicrud()
{
	contRDOnlyGUI* c = new contRDOnlyGUI(cont);
	
	c->show();
}

void DisciplinaGUI::guiaddCont()
{
	try {
		string denum = addC->text().toStdString();


		addC->clear();

		this->serv.addToContract(denum);

		//this->reloadList(this->serv.getContract());

		

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
	cont->service.notify();
}

void DisciplinaGUI::guiemptyCont()
{
	this->serv.clearContract();
	//this->reloadList(this->serv.getContract());
	cont->service.notify();
}

void DisciplinaGUI::guipopulateCont()
{
	int nr = populate->text().toInt();
	populate->clear();
	this->serv.fillRandom(nr);
	//this->reloadTable(this->contServ.getContract());
	cont->service.notify();
}

DisciplinaGUI::DisciplinaGUI(DisServ& se) :serv{ se }
{
	
		cont = new contCRUDGUI(serv);
		cont->initcontGUI();
		cont->reloadList(serv.getContract());
		cont->connectSignalSlots();

		contRo = new contRDOnlyGUI(cont);
		contRo->build_UI();
		initGUI();
		connectSignalSlots();
		reloadList(serv.getDList());

		//reloadcont(serv.getContract());
	
}