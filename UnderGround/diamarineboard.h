#ifndef DIAMARINEBOARD_H
#define DIAMARINEBOARD_H

#include <QDialog>
#include<QKeyEvent>
namespace Ui {
class DiaMarineBoard;
}

class DiaMarineBoard : public QDialog
{
    Q_OBJECT

public:
    explicit DiaMarineBoard(QWidget *parent = 0);
    ~DiaMarineBoard();

    void keyPressEvent(QKeyEvent *event);

private:
    Ui::DiaMarineBoard *ui;
};

#endif // DIAMARINEBOARD_H
