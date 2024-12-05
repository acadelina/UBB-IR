#pragma once
#include"Domain.h"
#include"QAbstractTableModel"

class MyModel : public QAbstractTableModel
{
	vector<Task> lista;

public:
	MyModel(const vector<Task>& lista) :lista{ lista } {};
	int rowCount(const QModelIndex& parent = QModelIndex()) const override
	{
		return lista.size();
	}
	int columnCount(const QModelIndex& parent = QModelIndex()) const override
	{
		return 4;
	}
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole)const override
	{
		if (role == Qt::DisplayRole)
		{
			Task t = lista[index.row()];
			if (index.column() == 0)
			{
				return QString::number(t.getid());
			}
			else if (index.column() == 1)
				return QString::fromStdString(t.getdesc());
			else if (index.column() == 2)
			{
				
				return QString::number(t.getprog().size());
			}
			else if (index.column() == 3)
				return QString::fromStdString(t.getstare());

		}
		return QVariant{};
	}
	void set_table(const vector<Task> t)
	{
		this->lista = t;
		auto topleft = createIndex(0, 0);
		auto botrig = createIndex(rowCount(), columnCount());
		emit layoutChanged();
		emit dataChanged(topleft, botrig);
	}
};