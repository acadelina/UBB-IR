#include"GUI.h"
#include<sstream>

void GUI::init()
{
	QHBoxLayout* lymain = new QHBoxLayout;
	this->setLayout(lymain);

	//tabela->setSelectionMode(QAbstractItemView::SingleSelection);
//	model = new MyModel{this->serv.getAll() };
	//tabela->setModel(model);
	tabel = new QTableWidget;
	tabel->setColumnCount(4);
	QWidget* left = new QWidget;
	QFormLayout* lyleft = new QFormLayout;
	left->setLayout(lyleft);

	edid = new QLineEdit;
	eddesc = new QLineEdit;
	edprg = new QLineEdit;
	edstare = new QLineEdit;

	lyleft->addRow(lblid, edid);
	lyleft->addRow(lbldesc, eddesc);
	lyleft->addRow(lblprog, edprg);
	lyleft->addRow(lblstare, edstare);


	btnadd = new QPushButton("Adauga");

	lyleft->addWidget(btnadd);

	edse = new QLineEdit;
	lyleft->addRow(lblse, edse);
	lymain->addWidget(left);
	lymain->addWidget(tabel);


}

void GUI::connect()
{
	QObject::connect(btnadd, &QPushButton::clicked, [this] {
		int id = edid->text().toInt();
		string desc = eddesc->text().toStdString();
		string stare = edstare->text().toStdString();
		vector<string> prog;
		string all = edprg->text().toStdString();
		auto ss = stringstream(all);
		string cuv;
		while (getline(ss, cuv, ' '))
		{
			prog.push_back(cuv);
		}
		try {
			serv.adaugare(id, desc, prog, stare);
			reload(serv.sort());
		}
		catch (RepoError& er)
		{
			QMessageBox::warning(this, "warning", QString::fromStdString(er.getmsg()));
		}

		});
	QObject::connect(edse, &QLineEdit::textChanged, [this] {
		if (edse->text().isEmpty())
			reload(serv.sort());
		else
		{
			string prog = edse->text().toStdString();
			reload(serv.search(prog));
		}
		});

}

void GUI::reload(vector<Task> t)
{
	tabel->clear();
	tabel->setRowCount(int(t.size()));
	int n = 0;
	for (auto& i : t)
	{
		tabel->setItem(n, 0, new QTableWidgetItem(QString::number(i.getid())));
		tabel->setItem(n, 1, new QTableWidgetItem(QString::fromStdString(i.getdesc())));
		tabel->setItem(n, 2, new QTableWidgetItem(to_string(i.getprog().size()).c_str()));
		tabel->setItem(n, 3, new QTableWidgetItem(QString::fromStdString(i.getstare())));
		n++;
	}
	/*for (int i = 0; i < t.size(); i++) {
		tabel->setCellWidget(i, 0, new QLabel(to_string(t[i].getid()).c_str()));
		tabel->setCellWidget(i, 1, new QLabel(t[i].getdesc().c_str()));
		tabel->setCellWidget(i, 2, new QLabel(t[i].getstare().c_str()));
		tabel->setCellWidget(i, 3, new QLabel(to_string(t[i].getprog().size()).c_str()));
	}*/
	//model->set_table(t);
}