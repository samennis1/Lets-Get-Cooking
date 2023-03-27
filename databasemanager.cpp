#include "databasemanager.h"
#include <iostream>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlRecord>
#include "databaseexception.h"

using namespace std;

DatabaseManager::DatabaseManager()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    qDebug() << this->path;
    db.setDatabaseName(this->path);

    if(!db.open()) {
        throw DatabaseException("Database Unable To Connect");
    } else {
        cout << "Found!" << endl;
    }

    QSqlQuery query;
    query.prepare("CREATE TABLE IF NOT EXISTS Recipe (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT NOT NULL, dietaryBits INTEGER DEFAULT 0);");
    if(query.exec()) {
        cout << "Success!";
    } else {
        cout << "Fail!";
    }

    QSqlQuery insert;

    insert.prepare("CREATE TABLE IF NOT EXISTS Ingredient (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT NOT NULL, quantity INTEGER NOT NULL, recipe_id INTEGER, price DOUBLE, FOREIGN KEY (recipe_id) REFERENCES Recipe(id));");
    if(insert.exec()) {
        cout << "Success 2" << endl;
    } else {
        cout << "Fail 2" << endl;
    }

    QSqlQuery get;
    get.prepare("SELECT * FROM Recipe");
    if(get.exec()) {
        int idName = get.record().indexOf("name");
        while(get.next()) {
            QString name = get.value(idName).toString();
               qDebug() << name;
        }
    }

}
