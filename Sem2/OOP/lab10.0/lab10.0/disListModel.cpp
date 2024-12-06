#include "disListModel.h"
#include <QMessageBox>

disListModel::disListModel(QObject* parent) : QAbstractTableModel(parent) {};

QVariant disListModel::data(const QModelIndex& index, int role) const
{
	const int row = index.row();
	const int column = index.column();
	if (role == Qt::DisplayRole)
	{
		switch (column)
		{
		case 0: return QString::fromStdString(disList.at(row).getDenum());
		case 1: return QString::number(disList.at(row).getOre());
		case 2: return QString::fromStdString(disList.at(row).getTip());
		case 3: return QString::fromStdString(disList.at(row).getProf());

		}
		//return QString("col %1").arg(column);
		return QString("R%1, C%2").arg(index.row() + 1).arg(index.column() + 1);
	}
	return QVariant();

}

int disListModel::rowCount(const QModelIndex&) const noexcept
{
	return (int)(disList.size());
}
int disListModel::columnCount(const QModelIndex&) const noexcept
{
	return 4;
}

QVariant disListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole)
	{
		if (orientation == Qt::Horizontal)
		{
			switch (section)
			{
			case 0: return QString("Denumire");
			case 1: return QString("Ore");
			case 2: return QString("Tip");
			case 3: return QString("Prof");

			}
			return QString("col %1").arg(section);
		}
		else {
			return QString("%1").arg(section);
		}
	}
	return QVariant();
}

void disListModel::setList(const vector<Disciplina>& _dList)
{
	this->disList = _dList;
	const QModelIndex topLeft = createIndex(0, 0);
	const QModelIndex bottomRight = createIndex(rowCount(), columnCount());
	dataChanged(topLeft, bottomRight);
	layoutChanged();
}