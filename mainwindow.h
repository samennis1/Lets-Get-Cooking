#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "newrecipe.h"
#include <qlist.h>
#include "card.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool displayingNoRecipeText = true;

private slots:
    void on_add_clicked();

    void on_exitButton_clicked();

public slots:
    void onRecipeAdded();

private:
    Ui::MainWindow *ui;
    NewRecipe* newRecipeWindow;
    QList<Card*> cards;
    void reloadRecipes();
};
#endif // MAINWINDOW_H
