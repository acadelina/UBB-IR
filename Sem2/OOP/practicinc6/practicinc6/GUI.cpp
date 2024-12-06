#include"GUI.h"

void GUI::init()
{
	tabela->setSelectionMode(QAbstractItemView::SingleSelection);
	model = new MyModel{ serv.sort() };
	tabela->setModel(model);

	QHBoxLayout* lymain = new QHBoxLayout;
	this->setLayout(lymain);

	QFormLayout* leftly = new QFormLayout;
	QWidget* left = new QWidget;
	left->setLayout(leftly);

	edid = new QLineEdit;
	eddim = new QLineEdit;
	edtabla = new QLineEdit;
	edjuc = new QLineEdit;
	edstare = new QLineEdit;

	leftly->addRow(lblid, edid);
	leftly->addRow(lbldim, eddim);
	leftly->addRow(lbltabla, edtabla);
	leftly->addRow(lbljuc, edjuc);
	leftly->addRow(lblstare, edstare);

	btnadd = new QPushButton("Adaugare");
	btnmod = new QPushButton("Modifica");

	leftly->addWidget(btnadd);
	leftly->addWidget(btnmod);

	lymain->addWidget(left);
	lymain->addWidget(tabela);
}

void GUI::connect()
{
	QObject::connect(btnadd, &QPushButton::clicked, [this] {
		int  id = edid->text().toInt();
		int  dim = eddim->text().toInt();
		string tabla = edtabla->text().toStdString();
		string juc = edjuc->text().toStdString();
		string stare = edstare->text().toStdString();
		try {
			serv.adaugare(id, dim, tabla, juc, stare);
			load();
		}
		catch(RepoExc& e)
		{
			QMessageBox::warning(this, "warning", QString::fromStdString(e.getmsg()));
		}
				});

			QObject::connect(btnmod, &QPushButton::clicked, [this] {
				int  id = edid->text().toInt();
				int  dim = eddim->text().toInt();
				string tabla = edtabla->text().toStdString();
				string juc = edjuc->text().toStdString();
				string stare = edstare->text().toStdString();
				try {
					serv.modificare(id, dim, tabla, juc, stare);
					load();
				}
				catch (RepoExc& e)
				{
					QMessageBox::warning(this, "warning", QString::fromStdString(e.getmsg()));
				}
						});

					QObject::connect(tabela->selectionModel(), &QItemSelectionModel::selectionChanged, [this] {
						int row = tabela->selectionModel()->currentIndex().row();
						int dim = tabela->model()->data(tabela->model()->index(row, 1), Qt::DisplayRole).toInt();
						auto data = tabela->model()->data(tabela->model()->index(row, 2), Qt::DisplayRole).toString();
						QFormLayout* ly = new QFormLayout;
						QWidget* joc = new QWidget;
						joc->setLayout(ly);
						for (int i = 0; i < dim; i += 3)
						{
							QWidget* temp = new QWidget;
							QVBoxLayout* lytemp = new QVBoxLayout;
							temp->setLayout(lytemp);
							lytemp->addWidget(new QPushButton(data[i]));
							lytemp->addWidget(new QPushButton(data[i + 1]));
							lytemp->addWidget(new QPushButton(data[i + 2]));
							ly->addRow(temp);

						}
						joc->show();

						});
}


void GUI::load()
{
	model->set_tabel(serv.sort());
}