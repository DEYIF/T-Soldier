#ifndef CHOOSE_H
#define CHOOSE_H

#include <QWidget>

namespace Ui {
class Choose;
}

class Choose : public QWidget
{
    Q_OBJECT

public:
    explicit Choose(QWidget *parent = 0);
    ~Choose();

private slots:
    void on_btn_ChooseLink_clicked();

private:
    Ui::Choose *ui;
};

#endif // CHOOSE_H
