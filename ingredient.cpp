#include "ingredient.h"
#include "iostream"
#include <string>;

using namespace std;

Ingredient::Ingredient(string name, int quantity, int price)
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
