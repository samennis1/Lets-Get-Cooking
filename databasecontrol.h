#ifndef DATABASECONTROL_H
#define DATABASECONTROL_H
#include <string>
#include "databasemanager.h"

class DatabaseControl
{
public:
    static DatabaseManager db;
    DatabaseControl();
    bool save(string);
    virtual void preSave();
};

#endif // DATABASECONTROL_H
