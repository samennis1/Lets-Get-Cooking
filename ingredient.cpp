#include "ingredient.h"
#include "iostream"
#include <string>;
#define defaultPrice 5
#define defaultQuantity 1

using namespace std;

Ingredient::Ingredient(string name, int quantity = defaultQuantity, int price = defaultPrice)
{
    this->name = name;
    this->quantity = quantity;
    this->totalPrice = price * quantity;
}

int Ingredient::getQuantity() {
    return quantity;
}

string Ingredient::getName() {
    return name;
}
