#include"GUI.h"

void GUI::init()
{
	QHBoxLayout* mainly = new QHBoxLayout;
	this->setLayout(mainly);

	tabela->setSelectionMode(QAbstractItemView::SingleSelection);
	model = new MyModel{ serv.sortP(),0 };
	tabela->setModel(model);

	edid = new QLineEdit;
	ednume = new QLineEdit;
	edtip = new QLineEdit;
	edpret = new QLineEdit;

	QWidget* left = new QWidget;
	QFormLayout* layoutleft = new QFormLayout;
	left->setLayout(layoutleft);

	layoutleft->addRow(lblid, edid);
	layoutleft->addRow(lblnume, ednume);
	layoutleft->addRow(lbltip, edtip);
	layoutleft->addRow(lblpret, edpret);

	btnadd = new QPushButton("Adauga");
	slide = new QSlider;

	layoutleft->addWidget(btnadd);
	layoutleft->addWidget(slide);

	mainly->addWidget(left);
	mainly->addWidget(tabela);



}

void GUI::connect()
{
	QObject::connect(btnadd, &QPushButton::clicked, [this] {
		int id = edid->text().toInt();
		string nume = ednume->text().toStdString();
		string tip = edtip->text().toStdString();
		double pret = edpret->text().toDouble();
		try {
			serv.adauga(id, nume, tip, pret);
		}
		catch (RepoError &er)
		{
			QMessageBox::warning(this, "Warning", QString::fromStdString(er.getmsg()));
		}
		catch (ValError& er)
		{
			QMessageBox::warning(this, "Warning", QString::fromStdString(er.getmsg()));
		}
		reload();

		});

	QObject::connect(slide, &QSlider::valueChanged, [this] {

		reload();
		});
	QObject::connect(tabela->selectionModel(), &QItemSelectionModel::selectionChanged, [this] {
		int row = tabela->selectionModel()->selectedIndexes().at(0).row();
		edid->setText(tabela->model()->data(tabela->model()->index(row, 0), Qt::DisplayRole).toString());
		ednume->setText(tabela->model()->data(tabela->model()->index(row, 1), Qt::DisplayRole).toString());
		edtip->setText(tabela->model()->data(tabela->model()->index(row, 2), Qt::DisplayRole).toString());
		edpret->setText(tabela->model()->data(tabela->model()->index(row, 3), Qt::DisplayRole).toString());

		});

}

void GUI::reload()
{
	model->set_tabel(serv.sortP(), slide->value());
}

