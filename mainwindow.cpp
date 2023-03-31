#include "mainwindow.h"
#include "QtGui/qpainter.h"
#include "qmenubar.h"
#include "ui_mainwindow.h"
#include "card.h"
#include "newrecipe.h"
#include "databasecontrol.h"
#include <QSqlQuery>
#include "review.h"
#include "about.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->noRecipes->show();
    onRecipeAdded();
    this->aboutAction = new QAction(0);
    this->aboutAction->setMenuRole(QAction::AboutRole);

#ifdef Q_OS_MAC
    QMenuBar* mainMenuBar = new QMenuBar(0);
    QMenu* mainMenu = new QMenu(0);
    mainMenuBar->addMenu(mainMenu);
    mainMenu->addAction(aboutAction);
    mainMenuBar->setVisible((true));
    qDebug() << mainMenuBar->isVisible() << mainMenuBar->isEnabled();
    setMenuBar(mainMenuBar);
    connect(aboutAction, &QAction::triggered, this, &MainWindow::showAboutDialog);
    #else
    QMenuBar* mainMenuBar = ui->menuBar;
    QMenu* mainMenu = mainMenuBar->addMenu(tr("&File"));
    QAction* aboutAction = new QAction(tr("&About"), this);
    mainMenu->addAction(aboutAction);
    connect(aboutAction, &QAction::triggered, this, &MainWindow::showAboutDialog);

#endif

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_add_clicked()
{
    newRecipeWindow->setModal(true);
    newRecipeWindow->exec();
}


void MainWindow::onRecipeAdded()
{
    newRecipeWindow = new NewRecipe(this);
    connect(newRecipeWindow, &NewRecipe::recipeAdded, this, &MainWindow::onRecipeAdded);
    reloadRecipes();
}

void MainWindow::reloadRecipes()
{
    qDeleteAll(cards);
    cards.clear();
    ui->CardsLayout->update();

    DatabaseControl d;

    QString query = "SELECT * FROM Recipe";
    DBRecordReturn result = d.execute(query);

    if(result.success) {
        while(result.returnedData.next()) {
            if(displayingNoRecipeText) {
                ui->noRecipes->deleteLater();
                displayingNoRecipeText = false;
            }
            result.returnedData.previous();
            QString name = Global::parseFieldFromRecord(result.returnedData, "name").toString();
            int id = Global::parseFieldFromRecord(result.returnedData, "id").toInt();
            qDebug() << "returnded name " << name;
            if(name == "false") continue;
            Card *c = new Card(nullptr, name, id);
            cards.append(c);
            ui->CardsLayout->addWidget(c);
            result.returnedData.next();
        }
    }
}


void MainWindow::on_exitButton_clicked()
{
    Review r;
    r.setModal(true);
    close();
    r.exec();
}


void MainWindow::on_actionNew_Recipe_triggered()
{
    About about;
    about.setModal(true);
    about.exec();
}

void MainWindow::showAboutDialog()
{
    About about;
    about.setModal(true);
    about.exec();
}

