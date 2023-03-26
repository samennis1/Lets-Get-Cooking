#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H
#include <string>
#include <QSqlDatabase>
#include <qdir.h>
#include "global.h";

using namespace std;
class DatabaseManager : public Global
{
public:
    DatabaseManager();
private:
    QSqlDatabase db;
};

#endif // DATABASEMANAGER_H
