#include "viewrecipe.h"
#include "ui_viewrecipe.h"
#include "recipe.h"
#include <QVector>
#include "qvector.h"

ViewRecipe::ViewRecipe(QWidget *parent, int id, QString name) :
    QDialog(parent),
    ui(new Ui::ViewRecipe)
{
    ui->setupUi(this);
    Recipe viewedRecipe(id, name);
    qDebug() << "NAME";
    qDebug() << viewedRecipe.getName();
    ui->recipeName->setText(viewedRecipe.getName());
    QVector<Ingredient> ingredientsRecipe(viewedRecipe.ingredients.begin(), viewedRecipe.ingredients.end());
    this->displayList = new IngredientsList(nullptr, ingredientsRecipe);
    ui->ingredientsList->setModel(this->displayList);

    for(int i = 0 ; i < 6; i++) {

    }
}

ViewRecipe::~ViewRecipe()
{
    delete ui;
}
