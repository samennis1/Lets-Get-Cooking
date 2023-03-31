#include "card.h"
#include "ui_card.h"
#include <QMouseEvent>
#include <QPainter>
#include "viewrecipe.h"

Card::Card(QWidget *parent, QString name, int id) :
    QWidget(parent),
    ui(new Ui::Card)
{
    ui->setupUi(this);
    ui->recipeName->setText(name);
    this->id = id;
}

Card::~Card()
{
    delete ui;
}

void Card::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.drawRect(0,0,width()-1, height()-1);

}

void Card::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        ViewRecipe viewer(nullptr, this->id, "Error");
        viewer.setModal(true);
        viewer.exec();
    }
}
