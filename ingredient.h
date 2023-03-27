#ifndef INGREDIENT_H
#define INGREDIENT_H
#include <QString>

using namespace std;
class Ingredient
{
    int quantity;
    QString name;
public:
    Ingredient(QString, int, double);
    int getQuantity();
    QString getName();
    friend class Recipe;
    friend class IngredientsList;
private:
    double totalPrice;
};

#endif // INGREDIENT_H
