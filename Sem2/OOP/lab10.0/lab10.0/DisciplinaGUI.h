#pragma once
#include <vector>
#include <string>
#include <QtWidgets/QApplication>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include<QCheckBox>
#include <QFormLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QRadioButton>
#include "serviceDis.h"
#include"disListModel.h"
//#include"ContarctGUI.h"
#include"contRoGUI.h"
#include"contractGUI.h"
#include"paint.h"

class DisciplinaGUI : public QWidget {
	friend class contCRUDGUI;
	friend class contRDOnlyGUI;
private:
	DisServ& serv;
	contCRUDGUI* cont;
	contRDOnlyGUI* contRo;

	QPushButton* btncont, * btnRo;
	//Contract& repo;
	//vector<Disciplina> dis;
	//adauga
	QPushButton* btnAdd;
	QLabel* adenum = new QLabel("Denumirea disciplinei: ");
	QLabel* aore = new QLabel("Numarul de ore al disciplinei: ");
	QLabel* atip = new QLabel("Tipul disciplinei: ");
	QLabel* aprof = new QLabel("Profesorul disciplinei: ");
	QLineEdit* addDenum;
	QLineEdit* addOre;
	QLineEdit* addTip;
	QLineEdit* addProf;

	//sterge
	QPushButton* btnsterge;
	QLabel* denumD = new QLabel{ "Denumirea discpiplinei: " };
	QLineEdit* denumDel;

	//modifica
	QPushButton* btnmodif;
	QLabel* mdenum = new QLabel("Denumirea disciplinei: ");
	QLabel* more = new QLabel("Numarul de ore al disciplinei: ");
	QLabel* mtip = new QLabel("Tipul disciplinei: ");
	QLabel* mprof = new QLabel("Profesorul disciplinei: ");
	QLineEdit* modDenum;
	QLineEdit* modOre;
	QLineEdit* modTip;
	QLineEdit* modProf;

	//sortare
	
	QLabel* labeldesc = new QLabel("Descrescator:");
	QCheckBox* desc = new QCheckBox;
	QLabel* labelsort = new QLabel("Sorteaza:");
	QPushButton* btnSortByDenum;
	QPushButton* btnSortByOre;
	QPushButton* btnSortByPT;

	//filtrare
	QLabel* filtrOre = new QLabel( "Numarul de ore dupa care se filtreaza:" );
	QLineEdit* fOre;
	QLabel* filtrProf = new QLabel("Cadrul didactic dupa care se filtreaza:" );
	QLineEdit* fProf;
	QPushButton* btnfiltrprof;
	QPushButton* btnfiltrore;

	

	QPushButton* btnReloadData;

	QTableView* table;
	disListModel* model;
	QListWidget* list;


	void initGUI();
	void connectSignalSlots();
	void reloadList(const std::vector<Disciplina> list);
	//void addDisNew();

	QVBoxLayout* raport = new QVBoxLayout;
	QWidget* din = new QWidget;

	QPushButton* undo;
	//tipurile de discipline
	//map rep = serv.raport();

	QPushButton* tip1;
	QPushButton* tip2;
	QPushButton* tip3;
	
	QPushButton* addCont, * emptyCont, * populateCont;
	QLineEdit* addC, * populate;
	QLabel* labelCAdd = new QLabel{ "Disciplina:" };
	//QPushButton* btnCont;
	//QPushButton* btncrud;
	//ContractGUI* cl = new ContractGUI{ serv,repo };
	//vector<ContractGUI*> cl;
	//vector<paintGUI*> pi;
	QLabel* clabel = new QLabel;
	QTableView* ctable = new QTableView;

public:
	DisciplinaGUI(DisServ& service);
	//: serv{ service } {
		//cont = new contCRUDGUI(serv);
		//cont->initcontGUI();
		//cont->reloadList(serv.getContract());
		//cont->connectSignalSlots();

		//contRo = new contRDOnlyGUI(cont);
		//contRo->build_UI();
		//initGUI();
		//connectSignalSlots();
		//reloadList(serv.getDList());
		
		//reloadcont(serv.getContract());
	//}
	//ordinea in care se sorteaza
	int ord;
	//adauga butoane
	void addbtns();
	//fucntie de adaugare
	void guiadd();
	//functie de stergere
	void guidelete();
	//modificare disciplina
	void guimod();
	//sortare dupa denumire
	void guisortbydenum();
	//sortare dupa ore
	void guisortbyore();
	//sortare dupa prof si tip
	void guisortbyPT();
	//functie care schimba ordinea
	void sortOrderChanged(int state);
	//undo
	void guiundo();
	void realgui();
	void umangui();
	void altelegui();
	void guicontract();
	void guicrud();
	void guiaddCont();
	void guiemptyCont();
	void guipopulateCont();
};
