#include"GUI.h"

void GUI::init()
{
	QVBoxLayout* lypaint = new QVBoxLayout;
	painter = new Painter{ this->serv.sameG() };
	painter->setLayout(lypaint);
	QHBoxLayout* lymain = new QHBoxLayout;
	this->setLayout(lymain);

	model = new MyModel { serv.sort(), serv.sameA(), serv.sameG() };
	tabela->setSelectionMode(QAbstractItemView::SingleSelection);
	tabela->setModel(model);

	QFormLayout* lyleft = new QFormLayout;
	QWidget* left = new QWidget;
	left->setLayout(lyleft);

	edid = new QLineEdit;
	edtitlu = new QLineEdit;
	edartist = new QLineEdit;
	edgen = new QLineEdit;

	lyleft->addRow(lblid, edid);
	lyleft->addRow(lbltitlu, edtitlu);
	lyleft->addRow(lblartist, edartist);
	lyleft->addRow(lblgen, edgen);

	btnadd = new QPushButton("Adauga");
	btnrem = new QPushButton("Sterge");

	lyleft->addWidget(btnadd);
	lyleft->addWidget(btnrem);

	lymain->addWidget(left);
	lymain->addWidget(tabela);



}

void GUI::connect()
{
	QObject::connect(tabela->selectionModel(), &QItemSelectionModel::selectionChanged, [this] {
		if (tabela->selectionModel()->selectedIndexes().isEmpty())
		{
			edid->setText("");
			edtitlu->setText("");
			edartist->setText("");
			edgen->setText("");
			return;
		}
		else
		{
			auto row = tabela->selectionModel()->selectedIndexes().at(0).row();
			auto id = tabela->model()->data(tabela->model()->index(row, 0), Qt::DisplayRole).toString();
			edid->setText(id);
			edtitlu->setText(tabela->model()->data(tabela->model()->index(row, 1), Qt::DisplayRole).toString());
			edartist->setText(tabela->model()->data(tabela->model()->index(row, 2), Qt::DisplayRole).toString());
			edgen->setText(tabela->model()->data(tabela->model()->index(row, 3), Qt::DisplayRole).toString());
		}
		});
	QObject::connect(btnadd, &QPushButton::clicked, [this] {
		int id = edid->text().toInt();
		string titlu = edtitlu->text().toStdString();
		string artist = edartist->text().toStdString();
		string gen = edgen->text().toStdString();
		serv.adauga(id, titlu, artist, gen);
		this->repaint();
		reload();

		});
	QObject::connect(btnrem, &QPushButton::clicked, [this]
		{
			int id = edid->text().toInt();
			serv.stergere(id);
			this->repaint();
			reload();
		});
}

void GUI::reload()
{
	model->set_mel(serv.getAll(), serv.sameA(), serv.sameG());
}

void Painter::paintEvent(QPaintEvent* ev)
{
	
}

void GUI::paintEvent(QPaintEvent* ev)
{
	QPainter p{ this };
	p.setPen(Qt::darkBlue);
	map<string, int> g = serv.sameG();
	int r = 0;

	for (int i = 0; i < g["pop"]; i++)
	{
		r++;
		p.drawEllipse(QPoint(0, 0), r * 8, r * 8);
	}
	r = 0;
	for (int i = 0; i < g["rock"]; i++)
	{
		r++;
		p.drawEllipse(QPoint(p.device()->width(), 0), r * 8, r * 8);
	}
	r = 0;
	for (int i = 0; i < g["folk"]; i++)
	{
		r++;
		p.drawEllipse(QPoint(0, p.device()->height()), r * 8, r * 8);
	}
	r = 0;
	for (int i = 0; i < g["disco"]; i++)
	{
		r++;
		p.drawEllipse(QPoint(p.device()->width(), p.device()->height()), r * 8, r * 8);
	}
}