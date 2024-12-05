#include"GUI.h"

void GUI::init()
{
	QHBoxLayout* lymain = new QHBoxLayout;
	this->setLayout(lymain);

	tabela->setSelectionMode(QAbstractItemView::SingleSelection);
	model = new MyModel{ serv.sort(),serv.rankuri() };
	tabela->setModel(model);

	QWidget* left = new QWidget;
	QFormLayout* lyleft = new QFormLayout;
	left->setLayout(lyleft);

	lbltitlu = new QLabel("Titlu");
	lyleft->addRow(lbltitlu, edtitlu);
	slide->setMaximum(10);
	lyleft->addRow(slide);
	btnrm = new QPushButton("Sterge");
	btnup = new QPushButton("Modifica");
	lyleft->addRow(btnrm);
	lyleft->addRow(btnup);
	
	lymain->addWidget(left);
	lymain->addWidget(tabela);
}

void GUI::connect()
{
	QObject::connect(btnrm, &QPushButton::clicked, [this]
		{
			int row = tabela->selectionModel()->selectedIndexes().at(0).row();
			int id = tabela->model()->data(tabela->model()->index(row, 0), Qt::DisplayRole).toInt();
			try {
				serv.sterge(id);
			}
			catch (exception& e)
			{
				QMessageBox::warning(this, "warning", QString::fromStdString("Artistul nu mai are alte melodii"));
			}
			load();
		});
	QObject::connect(btnup, &QPushButton::clicked, [this]
		{
			int row = tabela->selectionModel()->selectedIndexes().at(0).row();
			int id = tabela->model()->data(tabela->model()->index(row, 0), Qt::DisplayRole).toInt();
			int rank = slide->value();
			string titlu = edtitlu->text().toStdString();
			serv.modificare(id, titlu, rank);
			load();
		});
	QObject::connect(tabela->selectionModel(), &QItemSelectionModel::selectionChanged, [this]
		{
			int row = tabela->selectionModel()->selectedIndexes().at(0).row();
			slide->setValue(tabela->model()->data(tabela->model()->index(row, 3)).toInt());
			edtitlu->setText(tabela->model()->data(tabela->model()->index(row, 1)).toString());
		});

}

void GUI::load()
{
	model->set_tabel(serv.sort(), serv.rankuri());
	repaint();
}

void Painter::paintEvent(QPaintEvent* ev)
{

}

void GUI::paintEvent(QPaintEvent* ev)
{
	map<int, int> m = serv.rankuri();
	QPainter p{ this };
	p.setPen(Qt::darkGreen);
	int x = 1;
	for (int i = 0; i < m[6]; i++)
	{
		p.drawEllipse(QPoint(0, p.device()->height()), x * 5, x * 5);
		x += 4;
	}
	x = 1;
	for (int i = 0; i < m[6]; i++)
	{
		p.drawEllipse(QPoint(0,0), x * 5, x * 5);
		x += 4;
	}
	x = 1;
	for (int i = 0; i < m[6]; i++)
	{
		p.drawEllipse(QPoint(p.device()->width(), 0), x * 5, x * 5);
		x += 4;
	}
	x = 1;
	for (int i = 0; i < m[6]; i++)
	{
		p.drawEllipse(QPoint(p.device()->width(), p.device()->height()), x * 5, x * 5);
		x += 4;
	}
	/*for (int i = 0; i < 10; i++)
	{
		p.drawLine( x, p.device()->height(), x, p.device()->height()-4 * m[i]);
		x += 10;
	}*/
}