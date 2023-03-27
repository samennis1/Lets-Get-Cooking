#ifndef VIEWRECIPE_H
#define VIEWRECIPE_H

#include <QDialog>
#include "Ingredientslist.h"

namespace Ui {
class ViewRecipe;
}

class ViewRecipe : public QDialog
{
    Q_OBJECT

public:
    explicit ViewRecipe(QWidget *parent = nullptr, int id = 1, QString name = "Recipe");
    ~ViewRecipe();
    IngredientsList* displayList;

private:
    Ui::ViewRecipe *ui;
};

#endif // VIEWRECIPE_H
