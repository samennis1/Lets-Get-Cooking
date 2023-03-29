#ifndef REVIEW_H
#define REVIEW_H

#include <QDialog>

namespace Ui {
class Review;
}

class Review : public QDialog
{
    Q_OBJECT

public:
    explicit Review(QWidget *parent = nullptr);
    ~Review();

private slots:
    void on_slide_valueChanged(int value);

private:
    Ui::Review *ui;
};

#endif // REVIEW_H
