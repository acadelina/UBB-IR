#include"GUI.h"
#include<sstream>


void Window::init()
{
	wid->setWindowTitle(QString::fromStdString(stare));
	wid->setLayout(ly);
	QStringList l;
	l << "id" << "descriere" << "Stare" << "Programatori";

	tabel->setHorizontalHeaderLabels(l);
	tabel->setColumnCount(4);
	

	ly->addWidget(tabel);
	ly->addWidget(btnopen);
	ly->addWidget(btninp);
	ly->addWidget(btnclose);

}

void Window::connect()
{
	QObject::connect(btnopen, &QPushButton::clicked, [this] {
		
		int i = tabel->selectedItems().at(0)->row();
		
		int id = tabel->model()->data(tabel->model()->index(i, 0), Qt::DisplayRole).toInt();
		serv.modifica(id, "open");
		load();
		});
	QObject::connect(btninp, &QPushButton::clicked, [this] {
		
		int i = tabel->selectedItems().at(0)->row();
		int id = tabel->model()->data(tabel->model()->index(i, 0), Qt::DisplayRole).toInt();
		serv.modifica(id, "inprogress");
		load();
		});
	QObject::connect(btnclose, &QPushButton::clicked, [this] {
		
		int i = tabel->selectionModel()->selectedIndexes().at(0).row();
		int id = tabel->model()->data(tabel->model()->index(i, 0), Qt::DisplayRole).toInt();
		serv.modifica(id, "closed");
		load();
		});
}

void Window::load()
{
	tabel->clearContents();
	vector<Task> t = serv.stari(stare);
	tabel->setColumnCount(4);
	tabel->setRowCount(t.size());
	int nr = 0;
	for (auto a : t)
	{
		tabel->setItem(nr, 0, new QTableWidgetItem(QString::number(a.getid())));
		tabel->setItem(nr, 1, new QTableWidgetItem(QString::fromStdString(a.getdesc())));
		tabel->setItem(nr, 2, new QTableWidgetItem(QString::fromStdString(a.getstare())));
		tabel->setItem(nr, 3, new QTableWidgetItem(QString::number(a.getprog().size())));
		nr++;

	}
}

void GUI::init()
{
	QStringList l;
	l << "id" << "descriere" << "Stare" << "Programatori";
	tabel->setColumnCount(4);
	tabel->setHorizontalHeaderLabels(l);
	

	QWidget* left = new QWidget;
	QFormLayout* lyleft = new QFormLayout;
	QHBoxLayout* lymain = new QHBoxLayout;
	left->setLayout(lyleft);
	this->setLayout(lymain);

	lyleft->addRow(lblid, edid);
	lyleft->addRow(lbldesc, eddesc);
	lyleft->addRow(lblstare, edstare);
	lyleft->addRow(lblprog, edprog);
	lyleft->addWidget(btnadd);

	lyleft->addRow(lblcaut, edcaut);

	lymain->addWidget(left);
	lymain->addWidget(tabel);

}

void GUI::connect()
{
	QObject::connect(btnadd, &QPushButton::clicked, [this] {
		int id = edid->text().toInt();
		string desc = eddesc->text().toStdString();
		string stare = edstare->text().toStdString();
		string prog = edprog->text().toStdString();
		auto ss = stringstream(prog);
		vector<string> p;
		string cuv;
		while (getline(ss, cuv, ','))
			p.push_back(cuv);
		try {
			serv.adaugare(id, desc, stare, p);
			load(serv.getAll());
		}
		catch (RepoExc& re)
		{
			QMessageBox::warning(this, "warnning", QString::fromStdString(re.getmsg()));
		}
		});
	QObject::connect(edcaut, &QLineEdit::textChanged, [this] {
		string p = edcaut->text().toStdString();
		if (p == "")
			load(serv.getAll());
		else
		{
			load(serv.filtr(p));
		}
		});

}

void GUI::load(vector<Task> v)
{
	tabel->clearContents();
	tabel->setColumnCount(4);
	tabel->setRowCount(v.size());
	int nr = 0;
	for (auto a : v)
	{
		tabel->setItem(nr, 0, new QTableWidgetItem(QString::number(a.getid())));
		tabel->setItem(nr, 1, new QTableWidgetItem(QString::fromStdString(a.getdesc())));
		tabel->setItem(nr, 2, new QTableWidgetItem(QString::fromStdString(a.getstare())));
		tabel->setItem(nr, 3, new QTableWidgetItem(QString::number(a.getprog().size())));
		nr++;

	}
}

void GUI::windows()
{
	Window* w1 = new Window(serv, "open");
	Window* w2 = new Window(serv, "inprogress");
	Window* w3 = new Window(serv, "closed");
	w1->run();
	w2->run();
	w3->run();

}