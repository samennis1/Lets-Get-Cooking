#include "recipe.h"
#include "iostream"
#include <unordered_set>
#include <qsqlquery.h>
#include <QSqlRecord>
#include "databaseexception.h"

using namespace std;
Recipe::Recipe(string name)
{
    QString checkExists = "SELECT * FROM Recipe WHERE name = :name";
    Global::queryBind(checkExists, ":name", name);

    QString query = "INSERT INTO Recipe (name) VALUES (:name);";
    Global::queryBind(query, ":name", name);

    DBConditionalReturn runDBStatements = this->findOrCreate(checkExists, query);

    if(runDBStatements.firstStatementWasExecuted && !runDBStatements.secondStatementWasExecuted) {
        qDebug() << "Only First Query ";
        QSqlQuery recordData = std::move(runDBStatements.firstQueryData);
        QVariant parseID = Global::parseFieldFromRecord(recordData, "id");
        this->id = parseID.toInt();
        qDebug() << "Set id to " << this->id;
    } else {
        qDebug() << "Both Queries";
        DBRecordReturn run = this->execute(checkExists);
        if(run.success) {
            QVariant parseID = Global::parseFieldFromRecord(run.returnedData, "id");
            this->id = parseID.toInt();
            qDebug() << "Set id2 to " << this->id;
        }
    }
}

Ingredient Recipe::addIngredient(Ingredient a) {
   ingredients.push_back(a);
   QString query = "INSERT INTO Ingredient (name, quantity, recipe_id) VALUES (:name, :quantity, :recipe_id)";
   Global::queryBind(query, ":name", a.getName());
   Global::queryBind(query, ":quantity", a.getQuantity());
   Global::queryBind(query, ":recipe_id", this->id);
   this->execute(query);
   return a;
}

Recipe Recipe::operator+=(Ingredient const& a) {
    this->addIngredient(a);
    return *this;
}

bool Recipe::removeIngredient(QString name) {
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
        qDebug() << i->getName() << " : " << i->getQuantity();
    }

    cout << "----------" << endl;
}

void Recipe::preSave() {
    for(Ingredient i : this->ingredients) {
        QString query = "SELECT name FROM Ingredients WHERE name = :name, recipe_id = :id";
        Global::queryBind(query, ":name", i.getName());
        Global::queryBind(query, ":id", this->id);
    }
}

float Recipe::getTotalCost() {
    float total = 0;
    for(vector<Ingredient>::iterator i = ingredients.begin(); i != ingredients.end(); i++) {
        total = total + i->totalPrice;
    }

    return total;
}

void Recipe::addDietaryRestriction(DietaryRestriction restriction)
{
    dietaryRestrictions_.set(restriction);
}

void Recipe::removeDietaryRestriction(DietaryRestriction restriction)
{
    dietaryRestrictions_.reset(restriction);
}

bool Recipe::hasDietaryRestriction(DietaryRestriction restriction) const
{
    return dietaryRestrictions_.test(restriction);
}
