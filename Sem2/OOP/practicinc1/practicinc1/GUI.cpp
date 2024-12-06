#include"GUI.h"
#include<QPainter>

void GUI::init()
{
	QVBoxLayout* paintl = new QVBoxLayout;
	painter = new Painter{ this->serv.sameR() };
	painter->setLayout(paintl);

	QVBoxLayout* mainly = new QVBoxLayout;
	this->setLayout(mainly);

	QHBoxLayout* uplayout = new QHBoxLayout;
	QWidget* upwidet = new QWidget;
	upwidet->setLayout(uplayout);

	QFormLayout* uplayoutst = new QFormLayout;
	QWidget* upwidetst = new QWidget;
	upwidetst->setLayout(uplayoutst);

	edID = new QLineEdit;
	edTitlu = new QLineEdit;
	edArtist = new QLineEdit;
	edRank = new QLineEdit;

	uplayoutst->addRow(lblId, edID);
	uplayoutst->addRow(lblTitlu, edTitlu);
	uplayoutst->addRow(lblArtist, edArtist);
	uplayoutst->addRow(lblRank, edRank);

	btnmodif = new QPushButton("Update");
	btnsterg = new QPushButton("Sterge");

	slide = new QSlider;
	slide->setMaximum(10);
	uplayoutst->addWidget(slide);
	uplayoutst->addWidget(btnmodif);
	uplayoutst->addWidget(btnsterg);

	uplayout->addWidget(upwidetst);

	QVBoxLayout* uplayoutdr = new QVBoxLayout;
	QWidget* upwidetdr = new QWidget;
	upwidetdr->setLayout(uplayoutdr);

	model = new MyModel{ serv.getAll(),serv.sameR() };
	table->setSelectionMode(QAbstractItemView::SingleSelection);
	table->setModel(model);

	uplayoutdr->addWidget(table);
	uplayout->addWidget(upwidetdr);


	mainly->addWidget(upwidet);
	//mainly->addWidget(painter);

	
}

void GUI::connect()
{
	QObject::connect(table->selectionModel(), &QItemSelectionModel::selectionChanged, [this] {
		if (table->selectionModel()->selectedIndexes().isEmpty()) {
			edTitlu->setText("");
			slide->setValue(0);
			return;
		}
		else {
			
			auto row = table->selectionModel()->selectedIndexes().at(0).row();
			auto titlu = table->model()->data(table->model()->index(row, 1), Qt::DisplayRole).toString();
			auto rank = table->model()->data(table->model()->index(row, 3), Qt::DisplayRole).toInt();
			auto id = table->model()->data(table->model()->index(row, 0), Qt::DisplayRole).toString();
			edTitlu->setText(titlu);
			slide->setValue(rank);
			edID->setText(id);
		}
		});
	QObject::connect(btnmodif, &QPushButton::clicked, [this] {
		auto titlu = edTitlu->text().toStdString();
		int rank = int(slide->value());
		int id = edID->text().toInt();
		serv.modificR(rank, id);
		serv.modificT(id,titlu);
		this->repaint();
		reload();

		});

	QObject::connect(btnsterg, &QPushButton::clicked, [this] {
		int id = edID->text().toInt();
		serv.sterge(id);
		this->repaint();
		reload();
		});
}

void GUI::reload()
{
	model->set_mel(serv.getAll(), serv.sameR());
}

void Painter::paintEvent(QPaintEvent* ev) {

	QPainter p{ this };
	p.setPen(Qt::darkCyan);
	int r = 0;
	for (auto& c : rank) {
		int x = (r + 1) * 50;
		int z = x * c.second * 10;
		p.drawLine(x, 0, x, z);
	}
}

void GUI::paintEvent(QPaintEvent* ev) {
	QPainter p{ this };
	p.setPen(Qt::darkMagenta);
	map<int, int> rank=serv.sameR();
	int ind = 0;
	for (auto e : rank)
	{
		int x = (ind + 1) * 10;
		p.drawLine(x, p.device()->height(), x, p.device()->height() - e.second * 5);
		ind++;
	}
}