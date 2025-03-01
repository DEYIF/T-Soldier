#ifndef DIAVICTORY_H
#define DIAVICTORY_H

#include <QDialog>
#include<QKeyEvent>
namespace Ui {
class DiaVictory;
}

class DiaVictory : public QDialog
{
    Q_OBJECT

public:
    explicit DiaVictory(QWidget *parent = 0);
    ~DiaVictory();

    void keyPressEvent(QKeyEvent *event);

private:
    Ui::DiaVictory *ui;
};

#endif // DIAVICTORY_H
