#pragma once
#include<QAbstractItemModel>
#include<QBrush>
#include"Domain.h"

class MyModel : public QAbstractTableModel
{
	vector<Produs> p;
	int nr;
public:
	MyModel(const vector<Produs>& p, int nr) :p{ p }, nr{ nr } {};
	int rowCount(const QModelIndex& parent = QModelIndex()) const noexcept override
	{
		return p.size();
	}
	int columnCount(const QModelIndex& parent = QModelIndex())const noexcept override
	{
		return 5;
	}
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole)const noexcept override
	{
		if (role == Qt::BackgroundRole)
		{
			auto c = p[index.row()];
			int pret = c.getpret();
			if (pret < nr)
			{
				QBrush bg(Qt::darkRed);
				return bg;
			}
		}
		if (role == Qt::DisplayRole)
		{
			
			Produs pr = p[index.row()];
			if (index.column() == 0)
				return QString::number(pr.getid());
			else if (index.column() == 1)
				return QString::fromStdString(pr.getnume());
			else if (index.column() == 2)
				return QString::fromStdString(pr.gettip());
			else if (index.column() == 3)
				return QString::number(pr.getpret());
			else if (index.column() == 4)
				return QString::number(pr.getvocale());

		}
		return QVariant{};
	}

	QVariant headerData(int section, Qt::Orientation orient, int role)const noexcept override
	{
		if (role == Qt::DisplayRole)
		{
			if (orient == Qt::Horizontal)
			{
				if (section == 0)
					return QString("Id");
				else if (section == 1)
					return QString("Nume");
				else if (section == 2)
					return QString("Tip");
				else if (section == 3)
					return QString("Pret");
				else if (section == 4)
					return QString("Vocale");

			}
		}
		return QString("col %1").arg(section);
		return QVariant();
	}

	void set_tabel(vector<Produs> pr,int nr)
	{
		this->p = pr;
		this->nr = nr;
		auto topleft = createIndex(0, 0);
		auto botright = createIndex(rowCount(), columnCount());
		emit layoutChanged();
		emit dataChanged(topleft, botright);
	}
};