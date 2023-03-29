#include "about.h"
#include "QtGui/qpainter.h"
#include "ui_about.h"
#include "qdir.h"

About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);
}

About::~About()
{
    delete ui;
}
