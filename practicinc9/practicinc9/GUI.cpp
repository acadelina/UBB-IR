#include"GUI.h"
#include<sstream>

void GUI::init()
{
	QHBoxLayout* lymain = new QHBoxLayout;
	this->setLayout(lymain);

	QWidget* left = new QWidget;
	QFormLayout* lyleft = new QFormLayout;
	left->setLayout(lyleft);

	lyleft->addRow(lblid, edid);
	lyleft->addRow(lbldesc, eddesc);
	lyleft->addRow(lblst, edst);
	lyleft->addRow(lblprog, edprog);

	lyleft->addRow(btnadd);
	lyleft->addRow(lblcaut, edcaut);

	tabela->setSelectionMode(QAbstractItemView::SingleSelection);
	model = new MyModel(serv.sort(), "");
	tabela->setModel(model);

	lymain->addWidget(left);
	lymain->addWidget(tabela);

}

void GUI::connect()
{
	QObject::connect(edcaut, &QLineEdit::textChanged, [this] {
		string a = edcaut->text().toStdString();
		if (a != "")
			model->set_tabel(serv.filtrare(a), "");

		});
	QObject::connect(btnadd, &QPushButton::clicked, [this] {
		int id = edid->text().toInt();
		string d = eddesc->text().toStdString();
		string s = edst->text().toStdString();
		string p = edprog->text().toStdString();
		auto ss = stringstream(p);
		vector<string> arg;
		string cuv;
		while (getline(ss, cuv, ','))
			arg.push_back(cuv);
		serv.adaugare(id, d, arg, s);
		load();

		});
	
}

void GUI::load()
{
	model->set_tabel(serv.sort(), "");

}

void GUI::ferestre()
{
	Window* w1 = new Window(serv, "open");
	Window* w2 = new Window(serv, "inprogress");
	Window* w3 = new Window(serv, "closed");

	w1->run();
	w2->run();
	w3->run();
}