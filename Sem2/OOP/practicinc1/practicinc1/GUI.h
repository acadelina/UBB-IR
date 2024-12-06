#pragma once
#include"Serv.h"
#include"Model.h"
#include<QtWidgets>
#include<QLayout>
#include<QTableView.h>


class Painter : public QWidget {
private:
	map<int, int> rank;
public:

	explicit Painter(map<int, int> rank) : rank{ rank } {
		this->repaint();
	}
	void paintEvent(QPaintEvent* ev)override;
};
class GUI :public QWidget {
private:
	Serv& serv;
	MyModel* model;
	QTableView* table = new QTableView;

	QLabel* lblTitlu = new QLabel("Titlu:");
	QLabel* lblArtist = new QLabel("Artist:");
	QLabel* lblId = new QLabel("Id:");
	QLabel* lblRank = new QLabel("Rank:");

	QLineEdit* edTitlu = new QLineEdit;
	QLineEdit* edArtist= new QLineEdit;
	QLineEdit* edID = new QLineEdit;
	QLineEdit* edRank = new QLineEdit;


	QPushButton* btnmodif;
	QPushButton* btnsterg;

	QSlider* slide;
	Painter* painter;

	

	void init();
	void connect();
	void reload();
	void paintEvent(QPaintEvent* ev) override;
public:
	GUI(Serv& serv) :serv{ serv } {
		init();
		connect();
		reload();
		this->repaint();
	}
};
