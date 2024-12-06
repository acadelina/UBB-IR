#pragma once
#include <string>
#include <QWidget.h>
#include "serviceDis.h"
#include <QListWidget.h>
#include <QLayout.h>
#include <QFormLayout>
#include <QLineEdit>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qlistwidget.h>
#include <qheaderview.h>
#include <qmessagebox.h>
#include <QRadioButton>
#include <QMessageBox>
#include <qtablewidget.h>
#include"Observer.h"
#include"Export.h"
#include"crud.h"
#include"contract.h"
#include"paint.h"

class ContractGUI :public QWidget, public Observer
{
	friend class DisciplinaGUI;
private:
	DisServ& contServ;
	Contract& rep;
	vector<Disciplina> dis;
	void initGUIcmps();
	void connectSignalSlots();
	void reloadTable(const vector<Disciplina>& all);
	void update()override {
		reloadTable(rep.getAllCont());
	}
	QVBoxLayout* mainLayout = new QVBoxLayout;
	QListWidget* atWidget = new QListWidget;

	QLabel* aDenumire;

	QLineEdit* addDenumire;
	
	QLineEdit* addNumber;

	QLabel* Number;

	QLabel* fisier;
	QLineEdit* fis;

	QPushButton* adauga;
	QPushButton* adaugaRandom;
	QPushButton* gol;
	QPushButton* exportcsv;
	QPushButton* exporthtml;
	QPushButton* paint;

	QTableWidget* tabelAT;
	//paintGUI* pi = new paintGUI{ rep };
	
public:
	ContractGUI(DisServ& w,Contract& rep) :contServ{ w },rep{rep}
	{
		rep.addObserver(this);
		initGUIcmps();
		connectSignalSlots();
		reloadTable(rep.getAllCont());
	}
	~ContractGUI()
	{
		contServ.removeObserver(this);
	}

	void add();

	void addRandom();

	void empty();

	
	void expCSV();
	void expHTML();

	void paintgui();
	
};

