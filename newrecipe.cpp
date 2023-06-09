#include "newrecipe.h"
#include "recipe.h"
#include "ui_newrecipe.h"
#include "QSqlQueryModel"
#include "Ingredientslist.h"
#include "ingredient.h"
#include <QString>
#include <QHeaderView>

NewRecipe::NewRecipe(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewRecipe)
{
    ui->setupUi(this);
    this->displayList = new IngredientsList(nullptr, {});
    ui->ingredientsList->setModel(this->displayList);
}

NewRecipe::~NewRecipe()
{
    delete ui;
}

void NewRecipe::on_addIngredientButton_clicked()
{
   QString ingredientName = this->ui->ingredientName->text();
   double ingredientPrice = this->ui->ingredientPrice->value();
   int ingredientQuantity = this->ui->ingredientQuantity->value();

   if(ingredientQuantity <= 0) return;

   Ingredient* newIngredient = new Ingredient(ingredientName, ingredientQuantity, ingredientPrice);
   qDebug() << newIngredient->getName();
   qDebug() << newIngredient->getQuantity();
   this->displayList->addIngredient(*newIngredient);
}


void NewRecipe::on_buttonBox_accepted()
{
    QString name = this->ui->recipeName->text();
    Recipe newRecipe(name);
    QVector<Ingredient> list = this->displayList->getIngredients().toVector();
    int isVegan = this->ui->veganBox->checkState() ? Vegan : -1;
    int isVeg = this->ui->vegBox->checkState() ? Vegetarian : -1;
    int isGlutenFree = this->ui->glutenBox->checkState() ? GlutenFree : -1;
    int isDairyFree = this->ui->dairyBox->checkState() ? DairyFree : -1;
    int isNutFree = this->ui->nutBox->checkState() ? NutFree : -1;

    if (isVegan != -1)
        newRecipe.addDietaryRestriction(Vegan);

    if (isVeg != -1)
        newRecipe.addDietaryRestriction(Vegetarian);

    if (isGlutenFree != -1)
        newRecipe.addDietaryRestriction(GlutenFree);

    if (isDairyFree != -1)
        newRecipe.addDietaryRestriction(DairyFree);

    if (isNutFree != -1)
        newRecipe.addDietaryRestriction(NutFree);


    newRecipe.updateSQL();

    for(Ingredient ing : list) {
        newRecipe.addIngredient(ing);
    }
    qDebug() << "Emitting...";
    emit recipeAdded();
}

