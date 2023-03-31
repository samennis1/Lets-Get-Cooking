#ifndef RECIPE_H
#define RECIPE_H
#include <vector>
#include <string>
#include "databasecontrol.h"
#include "ingredient.h"
#include <bitset>

enum DietaryRestriction {
    Vegan = 0,
    Vegetarian = 1,
    GlutenFree = 2,
    DairyFree = 3,
    NutFree = 4
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
    void updateSQL();
    float getTotalCost();
    QString getName();
    void setDietaryBits(QString);

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
    std::bitset<5> dietaryRestrictions_{0};
    std::map<DietaryRestriction, int> dietaryPositions_ = {
        {Vegan, 0},
        {Vegetarian, 1},
        {GlutenFree, 2},
        {DairyFree, 3},
        {NutFree, 4}
    };
    QString name;
};

#endif // RECIPE_H
