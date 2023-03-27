#ifndef INGREDIENTSLIST_H
#define INGREDIENTSLIST_H

#include <QAbstractTableModel>
#include <QList>
#include "Ingredient.h"

class IngredientsList : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit IngredientsList(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

public slots:
    void addIngredient(Ingredient* ingredient);

private:
    QList<Ingredient*> list;
};

#endif // INGREDIENTSLIST_H
