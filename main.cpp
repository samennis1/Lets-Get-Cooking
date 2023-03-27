#include "databasemanager.h"
#include "mainwindow.h"
#include <iostream>
#include "databasecontrol.h"
#include "ingredient.h"
#include "ingredient.h"
#include "recipe.h"
#include <QApplication>

DatabaseManager globalDatabase;
DatabaseManager DatabaseControl::db = globalDatabase;
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Let's Get Cooking! | Version 3.14");
    w.show();
    return a.exec();
}
