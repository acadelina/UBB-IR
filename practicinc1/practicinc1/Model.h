#pragma once
#include"melodie.h"
#include<vector>
#include<QAbstractTableModel>
#include<QAbstractListModel>
#include<QWidget.h>
#include<map>

class MyModel :public QAbstractTableModel {
	vector<Melodie> mel;
	map<int, int> rank;
public:
	MyModel(const vector<Melodie>& mel, map<int, int> rnak) :mel{ mel }, rank{ rank } {};
	int rowCount(const QModelIndex& parent = QModelIndex())const noexcept override {
		return mel.size();
	}
	int columnCount(const QModelIndex& parent = QModelIndex())const override {
		return 6;
	}

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole)const override {
		if (role == Qt::DisplayRole)
		{
			Melodie m = mel[index.row()];
			if (index.column() == 0)
				return QString::number(m.getid());
			else if (index.column() == 1)
				return QString::fromStdString(m.gettitlu());
			else if (index.column() == 2)
				return QString::fromStdString(m.getartist());
			else if (index.column() == 3)
				return QString::number(m.getrank());
			else if (index.column() == 4)
				return QString::number(rank.at(m.getrank()));
		}
		return QVariant{};
	}

	void set_mel(const vector<Melodie> mel, map<int, int> rank)
	{
		this->mel = mel;
		this->rank = rank;
		auto topLeft = createIndex(0, 0);
		auto bottomR = createIndex(rowCount(), columnCount());
		emit layoutChanged();
		emit dataChanged(topLeft,bottomR);
	}
	
};
