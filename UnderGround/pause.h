#ifndef PAUSE_H
#define PAUSE_H

#include <QWidget>

namespace Ui {
class Pause;
}

class Pause : public QWidget
{
    Q_OBJECT

public:
    explicit Pause(QWidget *parent = 0);
    ~Pause();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Pause *ui;
};

#endif // PAUSE_H
