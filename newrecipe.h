#ifndef NEWRECIPE_H
#define NEWRECIPE_H
#include "Ingredientslist.h"
#include <QDialog>

namespace Ui {
class NewRecipe;
}

class NewRecipe : public QDialog
{
    Q_OBJECT

public:
    IngredientsList* displayList;
    explicit NewRecipe(QWidget *parent = nullptr);
    ~NewRecipe();

private slots:
    void on_addIngredientButton_clicked();

    void on_buttonBox_accepted();

signals:
    void recipeAdded();

private:
    Ui::NewRecipe *ui;
};

#endif // NEWRECIPE_H
