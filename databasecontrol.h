#ifndef DATABASECONTROL_H
#define DATABASECONTROL_H
#include <string>
#include "QtSql/QSqlQuery.h"
#include "databasemanager.h"

struct DBDefault {
    bool success;
};

struct DBResultField : DBDefault {
    QString result;
};

struct DBConditionalReturn {
    bool firstStatementWasExecuted;
    bool secondStatementWasExecuted;
    QSqlQuery firstQueryData;
    QSqlQuery secondQueryData;
};

struct DBRecordReturn : DBDefault {
   QSqlQuery returnedData;
};

class DatabaseControl
{
public:
    static DatabaseManager db;
    DatabaseControl();
    DBRecordReturn execute(string);
    DBRecordReturn execute(QString);
    DBResultField executeAndRetrieve(QString, QString);
    DBConditionalReturn findOrCreate(QString, QString);
    virtual void preSave();
};

#endif // DATABASECONTROL_H
