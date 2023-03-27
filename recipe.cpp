#include "recipe.h"
#include "iostream"
#include <unordered_set>
#include <qsqlquery.h>
#include <QSqlRecord>
#include "databaseexception.h"

using namespace std;
Recipe::Recipe(QString name)
{
    qDebug() << "NEW NON PASS!";
    QString checkExists = "SELECT * FROM Recipe WHERE name = :name";
    Global::queryBind(checkExists, ":name", name);

    QString query = "INSERT INTO Recipe (name) VALUES (:name);";
    Global::queryBind(query, ":name", name);
    setup(checkExists, query);
}

Recipe::Recipe(int id, QString fallbackName) {
    qDebug() << "PASS ID AND NAME " << fallbackName;
    QString checkExists = "SELECT * FROM Recipe WHERE id = :id";
    Global::queryBind(checkExists, ":id", id);

    QString query = "INSERT INTO Recipe (name) VALUES (:name);";
    Global::queryBind(query, ":name", fallbackName);
    setup(checkExists, query);
}

void Recipe::setup(QString queryOne, QString queryTwo) {
    qDebug() << "---- SETTING ----";
    DBConditionalReturn runDBStatements = this->findOrCreate(queryOne, queryTwo);
    bool anyRan = runDBStatements.firstStatementWasExecuted;
    bool onlyFirst = runDBStatements.firstStatementWasExecuted && !runDBStatements.secondStatementWasExecuted;

    if(onlyFirst) {
        qDebug() << "Only First Query ";
    } else {
        qDebug() << "Both Queries";
    }

    if(!anyRan) return throw DatabaseException("Error connecting to database");

    QSqlQuery recordData = std::move(onlyFirst ? runDBStatements.firstQueryData : runDBStatements.secondQueryData);
    QVariant parseID = Global::parseFieldFromRecord(recordData, "id");
    QVariant parsedName = Global::parseFieldFromRecord(recordData, "name");
    this->name = parsedName.toString();
    this->id = parseID.toInt();
    qDebug() << "Set id to " << this->id;

    qDebug() << "Set name to " << this->name;
    qDebug() << "---- END ----";
}

void Recipe::fetchIngredients() {
    QString query = "SELECT * FROM Ingredients WHERE recipe_id = :id";
    Global::queryBind(query, ":id", this->id);
    DBRecordReturn getIngredients = this->execute(query);
   if(getIngredients.success) {
       while(getIngredients.returnedData.next()) {
           getIngredients.returnedData.previous();
           QString name = Global::parseFieldFromRecord(getIngredients.returnedData, "name").toString();
           int quantity = Global::parseFieldFromRecord(getIngredients.returnedData, "quantity").toInt();
           double price = Global::parseFieldFromRecord(getIngredients.returnedData, "price").toDouble();

           Ingredient* found = new Ingredient(name, quantity, price);
           this->ingredients.push_back(*found);
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

QString Recipe::getName() {
    return this->name;
}
