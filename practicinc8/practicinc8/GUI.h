#pragma once
#include"MyModel.h"
#include"Serv.h"
#include<Qtwidgets>

class Painter :public QWidget
{
public:
	Painter() {
		this->repaint();
	}
	void paintEvent(QPaintEvent* ev)override;
};

class GUI :public QWidget
{
	Serv& serv;
	MyModel* model;
	QTableView* tabela = new QTableView;

	QLabel* lbltitlu = new QLabel;
	QLineEdit* edtitlu=new QLineEdit;
	QSlider* slide=new QSlider;
	
	QPushButton* btnrm;
	QPushButton* btnup;

	Painter* paint;
	
	void init();
	void connect();
	void load();
public:
	GUI(Serv& serv) :serv{ serv } {
		init();
		connect();
		load();
		repaint();
	}
	void paintEvent(QPaintEvent* ev)override;

};