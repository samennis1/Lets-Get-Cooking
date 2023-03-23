#include "databasemanager.h"
#include <iostream>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlRecord>

using namespace std;

DatabaseManager::DatabaseManager()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    qDebug() << this->path;
    db.setDatabaseName(this->path);

    if(!db.open()) {
        cout << "Error!" << endl;
    } else {
        cout << "Found!" << endl;
    }

    QSqlQuery query;
    query.prepare("CREATE TABLE IF NOT EXISTS Recipe (name VARCHAR(30) NOT NULL);");
    if(query.exec()) {
        cout << "Success!";
    } else {
        cout << "Fail!";
    }

    QSqlQuery insert;

    insert.prepare("INSERT INTO Recipe (name) VALUES (:name)");
    insert.bindValue(":name", "cool recipe");
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
