#include "help.h"
#include "ui_help.h"

Help::Help(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Help)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
}

Help::~Help()
{
    delete ui;
}

void Help::on_pushButton_clicked()
{
    this->close();
}
