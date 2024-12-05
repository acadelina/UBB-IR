#include"GUI.h"

void GUI::init()
{
	tabela->setSelectionMode(QAbstractItemView::SingleSelection);
	model = new MyModel{ serv.sort(),serv.tipuri(),0 };
	tabela->setModel(model);

	QHBoxLayout* lymain = new QHBoxLayout;
	this->setLayout(lymain);

	QFormLayout* lyleft = new QFormLayout;
	QWidget* left = new QWidget;
	left->setLayout(lyleft);

	edid = new QLineEdit;
	ednum = new QLineEdit;
	edtip = new QLineEdit;
	edpret = new QLineEdit;

	lyleft->addRow(lblid, edid);
	lyleft->addRow(lblnum, ednum);
	lyleft->addRow(lbltip, edtip);
	lyleft->addRow(lblpret, edpret);

	btnadd = new QPushButton("Adauga");
	lyleft->addWidget(btnadd);

	slide->setMaximum(50);
	lyleft->addWidget(slide);

	lymain->addWidget(left);
	lymain->addWidget(tabela);

}

void GUI::connect()
{
	QObject::connect(btnadd, &QPushButton::clicked, [this] {
		int id = edid->text().toInt();
		string n = ednum->text().toStdString();
		string t = edtip->text().toStdString();
		double p = edpret->text().toDouble();
		try {
			serv.adauga(id, n, t, p);
			load();
			//dinamicwind();
		}
		catch (RepoExc& e)
		{
			QMessageBox::warning(this, "warning", QString::fromStdString(e.getmsg()));
		}
		});
	QObject::connect(slide, &QSlider::valueChanged, [this] {
		int nr = slide->value();
		this->pret = nr;
		load();
		});
}

void GUI::load()
{
	model->set_tabel(serv.sort(), serv.tipuri(), pret);
}

void GUI::dinamicwind()
{
	auto l = serv.tipuri();
	for (auto e :l)
	{
		
		auto w=new Window (serv, e.first,e.second);
		w->run();
	}
}