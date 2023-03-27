#include "databasecontrol.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <iostream>

using namespace std;

DatabaseControl::DatabaseControl()
{
}

void DatabaseControl::updateSQL() {
    cout << "Default presave";
}

DBRecordReturn DatabaseControl::execute(QString queryString) {
    DBRecordReturn returnData;
    QSqlQuery saveQuery;
    QString queryText = queryString;
    saveQuery.prepare(queryText);
    qDebug() << "Executing... " << saveQuery.lastQuery();

    if(saveQuery.exec()) {
        qDebug() << "Exec!";
        returnData.returnedData = std::move(saveQuery);
        returnData.success = true;
    } else {
        qDebug() << "Nein!";
        returnData.success = false;
    }

    return returnData;
}

DBResultField DatabaseControl::executeAndRetrieve(QString queryString, QString field) {
    QSqlQuery saveQuery;
    QString queryText = queryString;
    saveQuery.prepare(queryText);

    DBResultField result;

    if(saveQuery.exec()) {
        result.success = true;
        result.result = Global::parseFieldFromRecord(saveQuery, field).toString();
    } else {
        result.success = false;
    }

    return result;
}


DBConditionalReturn DatabaseControl::findOrCreate(QString preQuery, QString postQuery) {
    DBConditionalReturn final;
    DBRecordReturn valid = this->execute(preQuery);
    if(!valid.success) {
        final.firstStatementWasExecuted = false;
        return final;
    } else {
        final.firstStatementWasExecuted = true;
        final.firstQueryData = std::move(valid.returnedData);

        if(final.firstQueryData.next()) {
            qDebug() << "Find or create found some initial next data " << Global::parseFieldFromRecord(final.firstQueryData, "name");
            final.firstQueryData.previous();
            return final;
        }

        DBRecordReturn run = this->execute(postQuery);
        final.secondStatementWasExecuted = run.success;
        final.secondQueryData = std::move(run.returnedData);
        return final;
    }
}
