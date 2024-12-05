#include"GUI.h"

void GUI::init()
{
	QVBoxLayout* paintl = new QVBoxLayout;
	paint = new Painter{ serv.roti(0)};
	paint->setLayout(paintl);

	QHBoxLayout* lymain = new QHBoxLayout;
	this->setLayout(lymain);
	QWidget* left = new QWidget;
	QFormLayout* lyleft = new QFormLayout;
	left->setLayout(lyleft);

	tabela->setSelectionMode(QAbstractItemView::SingleSelection);
	model = new MyModel{ serv.sort(),serv.sametip(),"tip" };
	tabela->setModel(model);

	edid = new QLineEdit;
	eddenum = new QLineEdit;
	edtip = new QLineEdit;
	edroti = new QLineEdit;

	lyleft->addRow(lblid, edid);
	lyleft->addRow(lbldenum, eddenum);
	lyleft->addRow(lbltip, edtip);
	lyleft->addRow(lblroti, edroti);

	btnadd = new QPushButton("Adauga");
	lyleft->addRow(btnadd);
	box = new QComboBox;
	lyleft->addWidget(box);

	lymain->addWidget(left);
	lymain->addWidget(tabela);

}

void GUI::connect()
{
	QObject::connect(btnadd, &QPushButton::clicked, [this] {
		int id = edid->text().toInt();
		string d = eddenum->text().toStdString();
		string t = edtip->text().toStdString();
		int r = edroti->text().toInt();

		try {
			serv.adaugare(id, d, t, r);
			load(tip);
			dinamicBox();
		}
		catch (RepoExc& ex)
		{
			QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getmsg()));
		}
		});
	QObject::connect(box, &QComboBox::currentIndexChanged, [this] {
		string tip = box->currentText().toStdString();
		load(tip);

		});
	QObject::connect(tabela->selectionModel(), &QItemSelectionModel::selectionChanged, [this]
		{
			auto row = tabela->selectionModel()->selectedIndexes().at(0).row();
			nrRoti = tabela->model()->data(tabela->model()->index(row, 3), Qt::DisplayRole).toInt();
			this->repaint();
		});

	
}

void GUI::load(string tip)
{
	model->set_tabela(serv.sort(), serv.sametip(), tip);
}

void GUI::dinamicBox()
{
	box->clear();
	map<string, int> m = serv.sametip();
	for (auto a : m)
	{
		box->addItem(QString::fromStdString(a.first));
	}

}

void Painter::paintEvent(QPaintEvent* ev)
{

}

void GUI::paintEvent(QPaintEvent* ev)
{
	
	QPainter p{ this };
	p.setPen(Qt::darkGreen);
	for (int i = 1; i <= nrRoti; i++)
		p.drawEllipse(QPoint(0, p.device()->height()), i * 8, i * 8);
}