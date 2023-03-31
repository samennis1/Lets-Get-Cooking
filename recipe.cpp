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

    if(!anyRan) return throw DatabaseException("Error connecting to database");

    QSqlQuery recordData = std::move(onlyFirst ? runDBStatements.firstQueryData : runDBStatements.secondQueryData);
    QVariant parseID = Global::parseFieldFromRecord(recordData, "id");
    QVariant parsedName = Global::parseFieldFromRecord(recordData, "name");
    QVariant dietaryBits = Global::parseFieldFromRecord(recordData, "dietaryBits");
    this->name = parsedName.toString();
    this->id = parseID.toInt();
    setDietaryBits(dietaryBits.toString());
    qDebug() << "Set id to " << this->id;
    qDebug() << "Set name to " << this->name;
    qDebug() << "---- END ----";

    if(onlyFirst) {
        qDebug() << "Only First Query ";
        fetchIngredients();
    } else {
        qDebug() << "Both Queries";
        setup(queryOne, "queryTwo");
    }
}

void Recipe::setDietaryBits(QString bits) {
    qDebug() << "PASSSED " << bits;
    int x = 0;
    for(int i = bits.size()-1; i >= 0; i--) {
        QChar b = bits[i];  // Adjust index to start at 0
        int bite = b.digitValue();
        qDebug() << "BIT " << b << " VALUE " << bite;
        if(bite > 0) {
            qDebug() << "Passing " << 6-i << "  ";
            addDietaryRestriction((DietaryRestriction) (x));
        }
        x++;
    }
}

void Recipe::fetchIngredients() {
    QString query = "SELECT * FROM Ingredient WHERE recipe_id = :id";
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
            qDebug() << "ADDING INGREDIENT " << name << price;
            getIngredients.returnedData.next();
        }
    }
}

Ingredient Recipe::addIngredient(Ingredient a) {
    ingredients.push_back(a);
    QString query = "INSERT INTO Ingredient (name, quantity, recipe_id, price) VALUES (:name, :quantity, :recipe_id, :price)";
    Global::queryBind(query, ":name", a.getName());
    Global::queryBind(query, ":quantity", a.getQuantity());
    Global::queryBind(query, ":recipe_id", this->id);
    Global::queryBind(query, ":price", a.totalPrice);
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

void Recipe::updateSQL() {
    QString query = "UPDATE Recipe SET dietaryBits = :bitValue WHERE id = :id";
    QString bits = QString::fromStdString(this->dietaryRestrictions_.to_string());
    Global::queryBind(query, ":bitValue", bits);
    Global::queryBind(query, ":id", this->id);
    this->execute(query);
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
    qDebug() << "ADDRESS OF DIETARY " << &dietaryRestrictions_;
    qDebug() << "PRE..." << QString::fromStdString(dietaryRestrictions_.to_string());
    qDebug() << "ADDING... " << restriction;
    int pos = dietaryPositions_[restriction];
    dietaryRestrictions_.set(pos);
    qDebug() << "ADD RESTRICTION..." << QString::fromStdString(dietaryRestrictions_.to_string());
    qDebug() << "ADDRESS OF DIETARY " << &dietaryRestrictions_;
}




void Recipe::removeDietaryRestriction(DietaryRestriction restriction)
{
    dietaryRestrictions_.reset(restriction);
}

bool Recipe::hasDietaryRestriction(DietaryRestriction restriction) const
{
    int pos = dietaryPositions_.at(restriction);
    return dietaryRestrictions_.test(pos);
}


QString Recipe::getName() {
    return this->name;
}
