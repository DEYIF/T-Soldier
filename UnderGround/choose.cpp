#include "choose.h"
#include "ui_choose.h"
#include<game.h>

Choose::Choose(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Choose)
{
    ui->setupUi(this);
}

Choose::~Choose()
{
    delete ui;
}

void Choose::on_btn_ChooseLink_clicked()
{
    Game* gam=new Game;
    gam->show();
    this->close();
}
