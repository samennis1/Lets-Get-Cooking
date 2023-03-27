#include "viewrecipe.h"
#include "ui_viewrecipe.h"
#include "recipe.h"
#include <QVector>
#include "qvector.h"
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
    QVector<Ingredient> ingredientsRecipe(viewedRecipe.ingredients.begin(), viewedRecipe.ingredients.end());
    qDebug() << "Ingredient SIZE " << ingredientsRecipe.size();
    this->displayList = new IngredientsList(nullptr, ingredientsRecipe);
    ui->ingredientsList->setModel(this->displayList);
    //VVGDN
    QList<QCheckBox*> list = {ui->veganBox, ui->vegBox, ui->glutenBox, ui->dairyBox, ui->nutBox};

    for(int i = 0 ; i < list.size(); i++) {
        int set = viewedRecipe.hasDietaryRestriction((DietaryRestriction) (i+1));
        if(set) {
            qDebug() << "Running " << i;
            list.at(i)->setCheckable(true);
            list.at(i)->setChecked(true);
        }
    }
}

ViewRecipe::~ViewRecipe()
{
    delete ui;
}
