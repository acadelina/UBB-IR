#pragma once
#include<QAbstractTableModel>
#include<QBrush>
#include"Domain.h"

class MyModel :public QAbstractTableModel
{
	vector<Tractor> t;
	map<string, int> sameT;
	string tip;
public:
	MyModel(const vector<Tractor>& t, map<string, int> sameT, string tip) :t{ t }, sameT{ sameT }, tip { tip } {};
	int rowCount(const QModelIndex& parent = QModelIndex())const override
	{
		return t.size();
	}
	int columnCount(const QModelIndex& parent = QModelIndex())const override
	{
		return 5;
	}
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole)const noexcept override
	{
		if (role == Qt::BackgroundRole)
		{
			
			Tractor tr = t[index.row()];
			if (tr.gettip() == tip)
			{
				QBrush bg(Qt::darkRed);
				return bg;

			}
		}
		if (role == Qt::DisplayRole)
		{
			Tractor tr = t[index.row()];
			if (index.column() == 0)
				return QString::number(tr.getid());
			else if (index.column() == 1)
				return QString::fromStdString(tr.getdenum());
			else if (index.column() == 2)
				return QString::fromStdString(tr.gettip());
			else if (index.column() == 3)
				return QString::number(tr.getRoti());
			else if (index.column() == 4)
				return QString::number(sameT.at(tr.gettip()));
		}
		return QVariant();
	}

	QVariant headerData(int section, Qt::Orientation orient, int role)const override
	{
		if (role == Qt::DisplayRole)
		{
			if (orient == Qt::Horizontal)
			{
				if (section == 0)
					return("ID");
				else if (section == 1)
					return ("Denumire");
				else if (section == 2)
					return ("TIP");
				else if (section == 3)
					return ("Numar roti");
				else if (section == 4)
					return ("Acelasi tip");
			}
		}
		return QVariant();
	}

	void set_tabela(vector<Tractor> t, map<string, int> sameT, string tip)
	{
		this->t = t;
		this->sameT = sameT;
		this->tip = tip;
		auto upleft = createIndex(0, 0);
		auto btrig = createIndex(rowCount(), columnCount());
		emit layoutChanged();
		emit dataChanged(upleft, btrig);
	}
};