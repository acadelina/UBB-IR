#pragma once
#include"Service.h"
#include"Melodie.h"
#include<QtWidgets/QApplication>
#include<QtWidgets>

class PGUI :public QWidget {
private:
	Serv& serv;

	QTableWidget* tabela;

	QLabel* id = new QLabel("Id produ: ");
	QLabel* nume = new QLabel("Nume produs: ");
	QLabel* tip = new QLabel("Tip produs: ");
	QLabel* pret = new QLabel("Pret produs: ");
	QLabel* producator = new QLabel("Producator produs: ");

	QLineEdit* Edid;
	QLineEdit* Ednume;
	QLineEdit* Edtip;
	QLineEdit* Edpret;
	QLineEdit* Edprod;

	QPushButton* btnAdd;
	QPushButton* btnrm;
	QPushButton* btnmod;
	QPushButton* btnfiltP;
	QPushButton* btnfiltN;
	QPushButton* btnsortN;
	QPushButton* btnsortP;

	QLabel* labeldesc = new QLabel("Descrescator: ");
	QCheckBox* desc = new QCheckBox;

	void initGUI();
	void connectSignalSlots();
	void reloadList(const std::vector<Produs> list);
public:
	PGUI(Serv& serv) :serv{ serv } {
		initGUI();
		connectSignalSlots();
		reloadList(serv.getList());
	}
	int ord;
	
	void guiadd();
	void guidelete();
	void guimod();
	void guisortN();
	//void guisortP();
	//void guifiltP();
	//void guifiltN();
	void sortOrderCh(int state);
};