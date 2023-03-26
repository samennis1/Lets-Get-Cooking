#ifndef RECIPE_H
#define RECIPE_H
#include <vector>
#include <string>
#include "databasecontrol.h"
#include "ingredient.h"
#include <bitset>

enum DietaryRestriction {
    None = 0,
    Vegan = 1,
    Vegetarian = 2,
    GlutenFree = 4,
    DairyFree = 8,
    NutFree = 16
};

using namespace std;
class Recipe : public DatabaseControl
{
    vector<Ingredient> ingredients;
    int id;
public:
    Recipe(string);
    bool removeIngredient(string);
    void listIngredients();
    void preSave();
    float getTotalCost();

    void addDietaryRestriction(DietaryRestriction restriction);
    void removeDietaryRestriction(DietaryRestriction restriction);
    bool hasDietaryRestriction(DietaryRestriction restriction) const;

    vector<Ingredient> getIngredients();
    Ingredient addIngredient(Ingredient);
    Recipe operator+=(Ingredient const& a);

    ~Recipe() {
        qDebug() << "Destructuring";
    }
private:
    std::bitset<5> dietaryRestrictions_;
};

#endif // RECIPE_H
