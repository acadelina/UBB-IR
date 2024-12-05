#pragma once
#include<QListView>
#include<QAbstractTableModel>
#include<QtWidgets>
#include"Domain.h"

class MyModel :public QAbstractTableModel {
	vector<Melodie> mel;
	map<string, int> g;
	map<string, int> a;
public:
	MyModel(const vector<Melodie>& mel, map<string, int> a, map<string, int> g) :mel{ mel }, a{ a }, g{ g } {}
	int rowCount(const QModelIndex& parent = QModelIndex()) const override
	{
		return mel.size();
	}
	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 6;
	}
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override
	{
		if (role == Qt::DisplayRole) {
			Melodie c = mel[index.row()];
			if (index.column() == 0)
				return QString::number(c.getid());
			else if (index.column() == 1)
				return QString::fromStdString(c.gettitlul());
			else if (index.column() == 2)
				return QString::fromStdString(c.getartist());
			else if (index.column() == 3)
				return QString::fromStdString(c.getgen());
			else if (index.column() == 4)
				return QString::number(a.at(c.getartist()));
			else if (index.column() == 5)
				return QString::number(g.at(c.getgen()));
		}
		return QVariant{};
	}
	/*QVariant headerData(int section, Qt::Orientation orient, int role)const override
	{
		if (role == Qt::DisplayRole)
		{
			if (orient == Qt::Horizontal)
			{
				switch (section)
				{
				case 0:return QString("Id");
				case 1:return QString("Titlu");
				case 2:return QString("Artist");
				case 3:return QString("Gen");
				}
				return QString("col %1").arg(section);
			}
			else {
				return QString("col %1").arg(section);
			}
		}
		return QVariant{};
	}*/
	void set_mel(const vector<Melodie> mel, map<string, int> ar, map<string, int> ge)
	{
		this->mel = mel;
		this->a = ar;
		this->g = ge;
		auto topLeft = createIndex(0, 0);
		auto botRight = createIndex(rowCount(), columnCount());
		emit layoutChanged();
		emit dataChanged(topLeft, botRight);
	}
};