#include "databasemanager.h"
#include "mainwindow.h"
#include <iostream>
#include "databasecontrol.h"
#include "recipe.h"
#include "ingredient.h"
#include <QApplication>

DatabaseManager globalDatabase;
DatabaseManager DatabaseControl::db = globalDatabase;
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Recipe System");
    Recipe sandwichRecipe;
    Ingredient *eggs = new Ingredient("Eggs", 3, 5.00);
    Ingredient *lettuce = new Ingredient("Lettuce", 1, 6.00);
    sandwichRecipe += *eggs;
    sandwichRecipe += *lettuce;
    sandwichRecipe.listIngredients();

    sandwichRecipe.preSave();
    qDebug() << sandwichRecipe.getTotalCost();
    w.show();
    return a.exec();
}
