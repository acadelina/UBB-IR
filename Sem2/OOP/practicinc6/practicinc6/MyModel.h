#pragma once
#include<QAbstractTableModel>
#include"Domain.h"

class MyModel :public QAbstractTableModel
{
	vector<Joc> v;
public:
	MyModel(const vector<Joc>& v) :v{ v } {};
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
		if (role == Qt::DisplayRole)
		{
			Joc j = v[index.row()];
			if (index.column() == 0)
				return QString::number(j.getid());
			else if (index.column() == 1)
				return QString::number(j.getdim());
			else if(index.column()==2)
				return QString::fromStdString(j.gettabla());
			else if (index.column() == 3)
				return QString::fromStdString(j.getjuc());
			else if (index.column() == 4)
				return QString::fromStdString(j.getstare());
		}
		return QVariant();
	}

	QVariant headerData(int section, Qt::Orientation orient, int role)
	{
		if (role == Qt::DisplayRole)
		{
			if (orient == Qt::Horizontal)
			{
				if (section == 0)
					return QString::fromStdString("ID");
				if (section == 1)
					return QString::fromStdString("Dimensiune");
				if (section == 2)
					return QString::fromStdString("Tabla");
				if (section == 3)
					return QString::fromStdString("Jucator");
				if (section == 4)
					return QString::fromStdString("Stare");
			}
		}
		return QVariant();
	}

	void set_tabel(vector<Joc> j)
	{
		this->v = j;
		auto upleft = createIndex(0, 0);
		auto darig = createIndex(rowCount(), columnCount());
		emit layoutChanged();
		emit dataChanged(upleft, darig);

	}
};