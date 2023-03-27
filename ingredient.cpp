#include "ingredient.h"
#include "iostream"
#include <string>;
#define defaultPrice 5
#define defaultQuantity 1

using namespace std;

Ingredient::Ingredient(QString name, int quantity = defaultQuantity, double price = defaultPrice)
{
    this->name = name;
    this->quantity = quantity;
    this->totalPrice = price * quantity;
}

int Ingredient::getQuantity() {
    return quantity;
}

QString Ingredient::getName() {
    return name;
}
