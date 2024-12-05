#pragma once
#include<QtWidgets>
#include<QAbstractTableModel>
#include"Domain.h"

class MyModel :public QAbstractTableModel
{
	vector<Produs> v;
	map<string, int> tipuri;
	int pret;
public:
	MyModel(const vector<Produs>& v, map<string, int> tipuri, int pret) :v{ v }, tipuri{ tipuri }, pret{ pret } {};
	int rowCount(const QModelIndex& parent = QModelIndex())const override
	{
		return v.size();
	}
	int columnCount(const QModelIndex& parent = QModelIndex())const override
	{
		return 5;
	}
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole)const override
	{
		if (role == Qt::BackgroundRole)
		{
			Produs p = v[index.row()];
			if (p.getpret() < pret)
			{
				QBrush b{ Qt::darkRed };
				return b;
			}
		}
		if (role == Qt::DisplayRole)
		{
			Produs p = v[index.row()];
			if (index.column() == 0)
				return QString::number(p.getid());
			else if (index.column() == 1)
				return QString::fromStdString(p.getnume());
			else if (index.column() == 2)
				return QString::fromStdString(p.gettip());
			else if (index.column() == 3)
				return QString::number(p.getpret());
			else if (index.column() == 4)
				return QString::number(tipuri.at(p.gettip()));
		}
		return QVariant{};
	}
	QVariant headerData(int position, Qt::Orientation orient, int role)
	{
		if (role == Qt::DisplayRole)
		{
			if (orient == Qt::Horizontal)
			{
				if (position == 0)
					return QString::fromStdString("Id");
				if (position == 1)
					return QString::fromStdString("Nume");
				if (position == 2)
					return QString::fromStdString("Tip");
				if (position == 3)
					return QString::fromStdString("Pret");
				if (position == 4)
					return QString::fromStdString("Acelasi tip");
			}
		}
		return QVariant();
	}

	void set_tabel(vector<Produs> v, map<string, int> m, int pret)
	{
		this->v = v;
		this->tipuri = m;
		this->pret = pret;
		auto topleft = createIndex(0, 0);
		auto botri = createIndex(rowCount(), columnCount());
		emit layoutChanged();
		emit dataChanged(topleft, botri);
	}
};