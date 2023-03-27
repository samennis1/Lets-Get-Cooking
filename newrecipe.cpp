#include "newrecipe.h"
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
    this->displayList = new IngredientsList;
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

   if(ingredientQuantity == 0) return;

   Ingredient* newIngredient = new Ingredient(ingredientName, ingredientQuantity, ingredientPrice);
   qDebug() << newIngredient->getName();
   qDebug() << newIngredient->getQuantity();
   this->displayList->addIngredient(newIngredient);
}

