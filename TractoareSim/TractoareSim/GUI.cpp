#include"GUI.h"

void GUI::initGUI()
{
	//QWidget* main = new QWidget;
	QHBoxLayout* lymain = new QHBoxLayout;
	this->setLayout(lymain);

	QStringList header;
	header << "ID" << "Denumire" << "Tip" << "Roti"<<"Acelasi tip";
	tabela = new QTableWidget(5, 10);
	tabela->setHorizontalHeaderLabels(header);

	lymain->addWidget(tabela);

	QWidget* right = new QWidget;
	QFormLayout* lyright = new QFormLayout;
	right->setLayout(lyright);

	edid = new QLineEdit;
	eddenum = new QLineEdit;
	edtip = new QLineEdit;
	edroti = new QLineEdit;
	lyright->addRow(lblid, edid);
	lyright->addRow(lbldenum, eddenum);
	lyright->addRow(lbltip, edtip);
	lyright->addRow(lblroti, edroti);

	btnadd = new QPushButton("ADAUGA TRACTOR");
	filt = new QPushButton("Filtreaza");

	lyright->addWidget(btnadd);
	lyright->addWidget(filt);

	lymain->addWidget(right);



}

void GUI::reload(vector<Tractor> tr)
{
	tabela->clearContents();
	tabela->setRowCount(int(tr.size()));
	int n = 0;
	for (auto& t : tr)
	{
		tabela->setItem(n, 0, new QTableWidgetItem (QString::number(t.getId())));
		tabela->setItem(n, 1, new QTableWidgetItem(QString::fromStdString(t.getDenum())));
		tabela->setItem(n, 2, new QTableWidgetItem(QString::fromStdString(t.getTip())));
		tabela->setItem(n, 3, new QTableWidgetItem(QString::number(t.getRoti())));
		int nr = serv.nrTip(t);
		tabela->setItem(n, 4, new QTableWidgetItem(QString::number(nr)));
		n++;
	}

}

void GUI::connect()
{
	QObject::connect(btnadd, &QPushButton::clicked,this, &GUI::guiadd);
	QObject::connect(filt, &QPushButton::clicked,this, &GUI::guifiltr);
}

void GUI::guiadd()
{
	try
	{
		int id = edid->text().toInt();
		string denum = eddenum->text().toStdString();
		string tip = edtip->text().toStdString();
		int roti = edroti->text().toInt();
		serv.adaugare(id, denum, tip, roti);
		reload(serv.sort());
	}
	catch (ValException &ve)
	{
		QMessageBox::warning(this, "Warning", QString::fromStdString(ve.getMsj()));
	}
	catch (RepoException& re)
	{
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.getMsj()));
	}
}

void GUI::guifiltr()
{
	try {
		string tip = edtip->text().toStdString();
		reload(serv.filtraret(tip));
	}
	catch (ValException& ve)
	{
		QMessageBox::warning(this, "Warning", QString::fromStdString(ve.getMsj()));
	}
	catch (RepoException& re)
	{
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.getMsj()));
	}
}