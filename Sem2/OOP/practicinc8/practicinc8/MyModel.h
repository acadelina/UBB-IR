#pragma once
#include<QAbstractTableModel>
#include<vector>
#include"Domain.h"

class MyModel :public QAbstractTableModel
{
	vector<Melodie> v;
	map<int, int> r;
public:
	MyModel(const vector<Melodie>& v, map<int, int> m) :v{ v }, r{ m } {};
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
			Melodie m = v[index.row()];
			if (index.column() == 0)
				return QString::number(m.getid());
			else if (index.column() == 1)
				return QString::fromStdString(m.gettitlu());
			else if (index.column() == 2)
				return QString::fromStdString(m.getartist());
			else if (index.column() == 3)
				return QString::number(m.getrank());
			else if (index.column() == 4)
				return QString::number(r.at(m.getrank()));

		}
		return QVariant{};
	}

	QVariant headerData(int position, Qt::Orientation orient, int role)const override
	{
		if (role == Qt::DisplayRole)
		{
			if (orient == Qt::Horizontal)
			{
				if (position == 0)
					return QString::fromStdString("Id");
				if (position == 1)
					return QString::fromStdString("Titlu");
				if (position == 2)
					return QString::fromStdString("Artist");
				if (position == 3)
					return QString::fromStdString("Rank");
				if (position == 4)
					return QString::fromStdString("Acelasi rank");
			}
		}
		return QVariant{};
	}

	void set_tabel(vector<Melodie> m, map<int, int> r)
	{
		this->v = m;
		this->r = r;
		auto topleft = createIndex(0, 0);
		auto rightbot = createIndex(rowCount(), columnCount());
		emit layoutChanged();
		emit dataChanged(topleft, rightbot);
	}
};