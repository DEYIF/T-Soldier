#ifndef DIA_H
#define DIA_H

#include <QWidget>
#include <QDialog>
#include<QKeyEvent>

namespace Ui {
class Dia;
}

class Dia : public QDialog
{
    Q_OBJECT

public:
    explicit Dia(QWidget *parent = 0);
    ~Dia();

    void keyPressEvent(QKeyEvent *event);

private slots:
    void on_pushButton_clicked();

private:
    Ui::Dia *ui;
};

#endif // DIA_H
