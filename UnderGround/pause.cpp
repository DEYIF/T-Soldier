#include "pause.h"
#include "ui_pause.h"

Pause::Pause(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Pause)
{
    ui->setupUi(this);
}

Pause::~Pause()
{
    delete ui;
}

void Pause::on_pushButton_clicked()
{
    this->close();
}
