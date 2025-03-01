#include "login.h"
#include"music.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login w;
    w.setWindowTitle(QString("T字军战士"));
    w.show();
    return a.exec();
}
