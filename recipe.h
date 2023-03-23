#ifndef RECIPE_H
#define RECIPE_H
#include <vector>
#include <string>
#include "databasecontrol.h"
#include "ingredient.h"

using namespace std;
class Recipe : public DatabaseControl
{
    vector<Ingredient> ingredients;
public:
    Recipe();
    bool removeIngredient(string);
    void listIngredients();
    vector<Ingredient> getIngredients();
    Ingredient addIngredient(Ingredient);
    void preSave();
    Recipe operator+=(Ingredient const& a);
    float getTotalCost();
};

#endif // RECIPE_H
