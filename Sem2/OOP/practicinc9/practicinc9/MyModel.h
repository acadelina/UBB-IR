#pragma once
#include<QAbstractTableModel>
#include"Domain.h"
#include<QBrush>

class MyModel :public QAbstractTableModel
{
	vector<Task> v;
	string stare;
public:
	MyModel(const vector<Task>& v,  string stare) :v{ v }, stare{ stare } {};
	int rowCount(const QModelIndex& parent = QModelIndex())const override
	{
		return v.size();
	}
	int columnCount(const QModelIndex& parent = QModelIndex())const override
	{
		return 4;
	}
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole)const override
	{
		if (role == Qt::BackgroundRole)
		{
			Task t = v[index.row()];
			if (t.getstare() == stare)
			{
				QBrush b { Qt::darkMagenta };
				return b;
			}
		}
		if (role == Qt::DisplayRole)
		{
			Task t = v[index.row()];
			if (index.column() == 0)
				return QString::number(t.getid());
			if (index.column() == 1)
				return QString::fromStdString(t.getdesc());
			if (index.column() == 2)
				return QString::fromStdString(t.getstare());
			if (index.column() == 3)
				return QString::number(t.getprog().size());
		}
		return QVariant{};
	}

	void set_tabel(vector<Task> t, string s)
	{
		this->v = t;
		this->stare = s;
		auto topleft = createIndex(0, 0);
		auto botrig = createIndex(rowCount(), columnCount());
		emit layoutChanged();
		emit dataChanged(topleft, botrig);
	}
};