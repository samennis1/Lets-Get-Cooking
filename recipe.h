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
    GlutenFree = 3,
    DairyFree = 4,
    NutFree = 5
};

using namespace std;
class Recipe : public DatabaseControl
{
    vector<Ingredient> ingredients;
    int id;
public:
    Recipe(QString);
    Recipe(int, QString);
    void setup(QString queryOne, QString queryTwo);
    void fetchIngredients();
    bool removeIngredient(QString);
    void listIngredients();
    void preSave();
    float getTotalCost();
    QString getName();

    void addDietaryRestriction(DietaryRestriction restriction);
    void removeDietaryRestriction(DietaryRestriction restriction);
    bool hasDietaryRestriction(DietaryRestriction restriction) const;

    vector<Ingredient> getIngredients();
    Ingredient addIngredient(Ingredient);
    Recipe operator+=(Ingredient const& a);

    friend class ViewRecipe;

    ~Recipe() {
        qDebug() << "Destructuring";
    }
private:
    std::bitset<5> dietaryRestrictions_;
    QString name;
};

#endif // RECIPE_H
