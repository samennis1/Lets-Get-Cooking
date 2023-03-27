#include "card.h"
#include "ui_card.h"

#include <QPainter>

Card::Card(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Card)
{
    ui->setupUi(this);
}

Card::~Card()
{
    delete ui;
}

// just to draw a border. could also use stylesheet
void Card::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.drawRect(0,0,width()-1, height()-1);

}
