#pragma once
#include"Serv.h"
#include"Domain.h"
#include"MyModel.h"
#include<Qtwidgets>

class Painter : public QWidget {
private:
	map<string, int> gen;
public:
	explicit Painter(map<string, int> gen) :gen{ gen } {
		this->repaint();
	}
	void paintEvent(QPaintEvent* ev)override;
};
class GUI :public QWidget
{
private:
	Serv& serv;
	MyModel* model;
	QTableView* tabela=new QTableView;
	

	

	QLabel* lblid = new QLabel("Id:");
	QLabel* lbltitlu = new QLabel("Titlu:");
	QLabel* lblartist = new QLabel("Artist:");
	QLabel* lblgen = new QLabel("Gen:");

	QLineEdit* edid= new QLineEdit;
	QLineEdit* edtitlu= new QLineEdit;
	QLineEdit* edartist= new QLineEdit;
	QLineEdit* edgen= new QLineEdit;

	QPushButton* btnadd;
	QPushButton* btnrem;

	Painter* painter;

	void init();
	void connect();
	void reload();
	void paintEvent(QPaintEvent* ev)override;
public:
	explicit GUI(Serv& serv) :serv{ serv } {
		init();
		connect();
		reload();
		this->repaint();
	};

};