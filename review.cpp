#include "review.h"
#include "ui_review.h"

Review::Review(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Review)
{
    ui->setupUi(this);
}

Review::~Review()
{
    delete ui;
}

void Review::on_slide_valueChanged(int value)
{
    ui->changenum->setText(QString::fromStdString(std::to_string(value)) + "%");
}

