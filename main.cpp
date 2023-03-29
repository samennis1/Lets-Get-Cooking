#include "databasemanager.h"
#include "mainwindow.h"
#include <iostream>
#include "databasecontrol.h"
#include "ingredient.h"
#include "ingredient.h"
#include "recipe.h"
#include <QApplication>
#define NAME "NAME";
#define ID "ID";

DatabaseManager globalDatabase;
DatabaseManager DatabaseControl::db = globalDatabase;
using namespace std;

union versionUnion {
    char name[100];
    double versionNumber;
};

struct activeVersionTitling {
    versionUnion v;
    string descriptor;
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    time_t timeNow;
    struct tm *localTimeSet;

    time( &timeNow );
    localTimeSet = localtime( &timeNow );

    int hour = localTimeSet->tm_hour;

    qDebug() << "HOUR NOW " << hour;

    bool isMorning = hour >= 6 && hour < 12;
    bool isAfternoon = hour >= 12 && hour < 18;

    activeVersionTitling manager;

    strcpy(manager.v.name, "Broken Edition");
    manager.descriptor = NAME;

    if(isMorning) {
        strcpy(manager.v.name,"Morning Edition");
    } else if(isAfternoon) {
        manager.v.versionNumber = 3.14;
        manager.descriptor = ID;
    } else {
        strcpy(manager.v.name,"Night Edition");
    }

    bool isID = manager.descriptor == ID;

    if(isID) {
        w.setWindowTitle("Let's Get Cooking! | Version " + QString::number(manager.v.versionNumber));
    } else {
        w.setWindowTitle("Let's Get Cooking! | " + QString::fromStdString(manager.v.name));
    }

    w.show();
    return a.exec();
}
