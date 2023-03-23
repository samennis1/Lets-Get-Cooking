#ifndef INGREDIENT_H
#define INGREDIENT_H
#include <string>

using namespace std;
class Ingredient
{
    int quantity;
    string name;
public:
    Ingredient(string, int, int);
    int getQuantity();
    string getName();
    friend class Recipe;
private:
    float totalPrice;
};

#endif // INGREDIENT_H
