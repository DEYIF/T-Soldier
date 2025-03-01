#include "dia.h"
#include "ui_dia.h"

Dia::Dia(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dia)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    setFixedSize(1247,586);
    setAttribute(Qt::WA_TranslucentBackground);
}

Dia::~Dia()
{
    delete ui;
}

void Dia::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()){
    case Qt::Key_Space:
        this->close();
        break;
    }
}

void Dia::on_pushButton_clicked()
{
    this->close();
}
