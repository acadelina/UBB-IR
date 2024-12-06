#pragma once
#include <qwidget.h>
#include "observer.h"
#include "DisciplinaGUI.h"

class contCRUDGUI : public QWidget, public Observer
{
	friend class DisciplinaGUI;
	// cos CRUD GUI

public:
	// service-ul curent
	DisServ& service;
private:
	DisciplinaGUI* main;

	// lista de masini de spalat
	QListWidget* windowList;

	// butoanele pentru meniul de masini de spalat
	QPushButton* btnEmpty, * btnPopulate, * btnAcasa;
	//QPushButton* butonAcasa;


	// labels
	QLabel* labelAdd = new QLabel("Introduceti o denumire:");
	QLabel* labelPopulate = new QLabel("Introduceti un numar:");

	QLineEdit* populate;


	// populam lista de masini de spalat
	void generatecontGUI();

	// initializam fereastra pentru lista de spalat
	void initcontGUI();

	// reincarcam lista de masini de spalat
	void reloadList(vector<Disciplina> dList);

	// conectam butoanele
	void connectSignalSlots();

	void update() override
	{
		reloadList(service.getContract());
	}

public:
	contCRUDGUI(DisServ& cS) : service{ cS } {};
	~contCRUDGUI()
	{
		service.removeObserver(this);
	}
};