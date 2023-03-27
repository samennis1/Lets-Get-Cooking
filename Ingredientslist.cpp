#include "Ingredientslist.h"
#include "global.h"

IngredientsList::IngredientsList(QObject *parent)
    : QAbstractTableModel(parent)
{
}

int IngredientsList::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return this->list.size();
}

int IngredientsList::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return 3;
}

QVariant IngredientsList::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return tr("Ingredient Name");
        case 1:
            return tr("Quantity");
        case 2:
            return tr("Total €");
        default:
            return QVariant();
        }
    } else {
        return QString("#%1").arg(section);
    }
}

QVariant IngredientsList::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if(role == Qt::DisplayRole) {
        Ingredient* getIngredient = this->list[index.row()];
        if(index.column() == 0) {
            return getIngredient->getName();
        } else if(index.column() == 1) {
            return getIngredient->getQuantity();
        } else if(index.column() == 2) {
            return "€" + QString::number(getIngredient->totalPrice, 'f', 2);
        }
    }

    return QVariant();
}

void IngredientsList::addIngredient(Ingredient* ingredient) {
    const int index = list.size();
    beginInsertRows(QModelIndex(), index, index);
    list.append(ingredient);
    endInsertRows();
}
