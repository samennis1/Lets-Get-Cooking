#ifndef GLOBAL_H
#define GLOBAL_H
#include <QString>
#include <Qdir>
#include <string>;
#include <QSqlQuery>
#include <QSqlRecord>


using namespace std;

class Global
{
public:
    Global();
    QDir dir;
    QString path = QDir::currentPath() + "/database.sqlite";
    template <typename T>
    static inline string numberToString(T value) {
        return std::to_string(value);
    }
    template <typename Value>
    static inline QString queryBind(QString &base, QString name, Value replacement) {
        QString sqlSafeReplacement;
        if constexpr (std::is_same_v<Value, std::string>) {
            sqlSafeReplacement = "\"" + QString::fromStdString(replacement) + "\"";
        } else if constexpr (std::is_same_v<Value, int>) {
            sqlSafeReplacement = QString::number(replacement);
        }
        return base.replace(name, sqlSafeReplacement);
    }
    static QVariant parseFieldFromRecord(QSqlQuery &query, QString s) {
        int idName = query.record().indexOf(s);
        QVariant result = false;
        while(query.next()) {
            result = query.value(idName);
            break;
        }
        qDebug() << "GLOBAL PARSING:: FOUND " << result.toString();
        return result;
    }
};

#endif // GLOBAL_H
