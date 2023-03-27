#ifndef CARD_H
#define CARD_H

#include <QWidget>

namespace Ui {
class Card;
}

class Card : public QWidget
{
    Q_OBJECT

public:
    int id;
    explicit Card(QWidget *parent = nullptr, QString recipeName = "", int id = 1);
    ~Card();

private:
    Ui::Card *ui;

    // QWidget interface
protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
};

#endif // CARD_H
