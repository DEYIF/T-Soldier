#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include<setting.h>
#include<QKeyEvent>
#include<QMouseEvent>
namespace Ui {
class Login;
}

class Login : public QMainWindow
{
    Q_OBJECT
private:

public:
    explicit Login(QWidget *parent = 0);
    ~Login();
    Setting* set=new Setting;
    void keyPressEvent(QKeyEvent *event);
    void settingShow();//显示set
private slots:
    void on_btn_setting_clicked();
    void on_btn_begin_clicked();

    void on_pushButton_clicked();

public slots:


private:
    Ui::Login *ui;
};

#endif // LOGIN_H
