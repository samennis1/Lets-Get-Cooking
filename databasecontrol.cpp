#include "databasecontrol.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <iostream>

using namespace std;

DatabaseControl::DatabaseControl()
{
}

void DatabaseControl::preSave() {
    cout << "Default presave";
}

bool DatabaseControl::save(string queryString) {
    QSqlQuery saveQuery;
    QString queryText = QString::fromStdString(queryString);
    saveQuery.prepare(queryText);

    if(saveQuery.exec()) {
        return true;
    } else {
        return false;
    }
}
