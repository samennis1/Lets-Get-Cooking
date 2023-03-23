#include "recipe.h"
#include "iostream"

using namespace std;
Recipe::Recipe()
{

}

Ingredient Recipe::addIngredient(Ingredient a) {
   ingredients.push_back(a);
   return a;
}

Recipe Recipe::operator+=(Ingredient const& a) {
    this->addIngredient(a);
    return *this;
}

bool Recipe::removeIngredient(string name) {
    bool foundAndDeleted = false;
   for(vector<Ingredient>::iterator i = ingredients.begin(); i != ingredients.end(); i++) {
       if(i->getName() == name) {
           ingredients.erase(i);
           foundAndDeleted = true;
           break;
       }
   }

   return foundAndDeleted;
}

void Recipe::listIngredients() {
    cout << "----------" << endl;
    for(vector<Ingredient>::iterator i = ingredients.begin(); i != ingredients.end(); i++) {
        cout << i->getName() << " : " << i->getQuantity() << endl;
    }

    cout << "----------" << endl;
}

void Recipe::preSave() {
    cout << "presave";
}

float Recipe::getTotalCost() {
    float total = 0;
    for(vector<Ingredient>::iterator i = ingredients.begin(); i != ingredients.end(); i++) {
        total = total + i->totalPrice;
    }

    return total;
}
