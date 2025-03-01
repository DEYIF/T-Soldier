#ifndef DIAMOP_H
#define DIAMOP_H

#include <QDialog>
#include<QKeyEvent>
namespace Ui {
class DiaMop;
}

class DiaMop : public QDialog
{
    Q_OBJECT

public:
    explicit DiaMop(QWidget *parent = 0);
    ~DiaMop();

    void keyPressEvent(QKeyEvent *event);

private:
    Ui::DiaMop *ui;
};

#endif // DIAMOP_H
