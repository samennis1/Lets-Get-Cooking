#include "viewrecipe.h"
#include "ui_viewrecipe.h"
#include "recipe.h"
#include <QVector>
#include <iostream>

ViewRecipe::ViewRecipe(QWidget *parent, int id, QString name) :
    QDialog(parent),
    ui(new Ui::ViewRecipe)
{
    ui->setupUi(this);
    Recipe viewedRecipe(id, name);
    qDebug() << "NAME";
    qDebug() << viewedRecipe.getName();
    ui->recipeName->setText(viewedRecipe.getName());
    // Deep Copy
    QVector<Ingredient> ingredientsRecipe(viewedRecipe.ingredients.begin(), viewedRecipe.ingredients.end());
    qDebug() << "Ingredient SIZE " << ingredientsRecipe.size();
    this->displayList = new IngredientsList(nullptr, ingredientsRecipe);
    ui->ingredientsList->setModel(this->displayList);
    //VVGDN
    QList<QCheckBox*> list = {ui->veganBox, ui->vegBox, ui->glutenBox, ui->dairyBox, ui->nutBox};

    for (const auto& [restriction, index] : viewedRecipe.dietaryPositions_) {
        int set = viewedRecipe.hasDietaryRestriction(restriction);
        if (set) {
            qDebug() << "Checking checkbox for " << index;
            list.at(index)->setCheckable(true);
            list.at(index)->setChecked(true);
        }
    }




}

ViewRecipe::~ViewRecipe()
{
    delete ui;
}
