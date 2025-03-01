#ifndef DIABOARD_H
#define DIABOARD_H

#include <QDialog>
#include<QKeyEvent>

namespace Ui {
class DiaBoard;
}

class DiaBoard : public QDialog
{
    Q_OBJECT

public:
    explicit DiaBoard(QWidget *parent = 0);
    ~DiaBoard();

    void keyPressEvent(QKeyEvent *event);

private:
    Ui::DiaBoard *ui;
};

#endif // DIABOARD_H
