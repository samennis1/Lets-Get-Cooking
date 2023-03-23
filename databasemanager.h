#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H
#include <string>
#include <QSqlDatabase>
#include <qdir.h>

using namespace std;
class DatabaseManager
{
public:
    QDir dir;
    QString path = QDir::currentPath() + "/database.sqlite";
    DatabaseManager();
private:
    QSqlDatabase db;
};

#endif // DATABASEMANAGER_H
