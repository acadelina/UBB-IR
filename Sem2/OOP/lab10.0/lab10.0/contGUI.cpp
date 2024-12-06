#include "contractGUI.h"


void contCRUDGUI::initcontGUI()
{

	//main layout
	QHBoxLayout* lyMain = new QHBoxLayout{};
	setLayout(lyMain);

	//left part
	QWidget* left = new QWidget;
	QVBoxLayout* lyleft = new QVBoxLayout;
	left->setLayout(lyleft);

	// schimba pe lista de masini de spalat
	QWidget* form0 = new QWidget;
	QFormLayout* lyform0 = new QFormLayout;
	form0->setLayout(lyform0);
	btnAcasa = new QPushButton("Schimba pe meniul principal");
	lyform0->addWidget(btnAcasa);
	lyleft->addWidget(form0);


	// popularea listei de masini de spalat
	QWidget* form2 = new QWidget;
	QFormLayout* lyform2 = new QFormLayout;
	form2->setLayout(lyform2);
	populate = new QLineEdit;
	lyform2->addRow(labelPopulate, populate);
	btnPopulate = new QPushButton("Genereaza contract");
	lyform2->addWidget(btnPopulate);
	lyleft->addWidget(form2);

	// golirea listei de masini de spalat
	btnEmpty = new QPushButton("Goleste contract");
	lyleft->addWidget(btnEmpty);


	// lista curenta de masini
	QWidget* right = new QWidget;
	QHBoxLayout* lyright = new QHBoxLayout;
	right->setLayout(lyright);
	windowList = new QListWidget;
	lyright->addWidget(windowList);

	lyMain->addWidget(left);
	lyMain->addWidget(right);
}

void contCRUDGUI::connectSignalSlots()
{
	service.addObserver(this);
	QObject::connect(btnEmpty, &QPushButton::clicked, [&]()
		{
			this->service.clearContract();
			this->reloadList(this->service.getContract());
			QMessageBox::information(this, "Info", QString::fromStdString("Lista a fost golita cu succes!"));
		});
	QObject::connect(btnPopulate, &QPushButton::clicked, this, &contCRUDGUI::generatecontGUI);
	QObject::connect(btnAcasa, &QPushButton::clicked, [&]()
		{
			hide();
		});
}

void contCRUDGUI::generatecontGUI()
{
	
		int nr = populate->text().toInt();
		populate->clear();
		this->service.fillRandom(nr);
		this->reloadList(this->service.getContract());
		QMessageBox::information(this, "Info", QString::fromStdString("Masinile au fost adaugate cu succes!"));
		service.notify();
	
}

void contCRUDGUI::reloadList(const std::vector<Disciplina> all)
{
	windowList->clear();
	int n = 0;
	for (const auto& a : all)
	{
		QString itemtext = QString::fromStdString(a.getDenum()) + ", " + QString::number(a.getOre()) + ", " + QString::fromStdString(a.getTip()) + ", " + QString::fromStdString(a.getProf());
		QListWidgetItem* item = new QListWidgetItem(itemtext);
		windowList->addItem(item);

	}
}