#include "enemy.h"



Enemy::Enemy(QWidget *parent) : QWidget(parent)
{
    this->EHp=200;
    this->EmaxHp=200;
    this->EEn=100;
    this->Ewid=100;
    this->Ehei=100;
    this->Ex=1300;
    this->Ey=600;
    Edirection=0;
    goCount=0;
    //weapon=0;
    Epics[0].load(":/Pictures/GobFor.png");
    Epics[1].load(":/Pictures/BokoBlinRight.png");
    Epics[2].load(":/Pictures/GobFor.png");
    Epics[3].load(":/Pictures/GobFor.png");
    Epics[4].load(":/Pictures/BokoBlinRight.png");
    EDeath.load(":/Pictures/DeathHead.png");
    Soil.load(":/Pictures/MapSoil.png");

}

//判断Enemy是否在某个区域内
bool Enemy::enemyIsIn(int left, int right, int up, int down)
{
    if(this->Ex<=right&&this->Ex>=left&&this->Ey<=down&&this->Ey>=up){
        return true;
    }
    else return false;
}

//Enemy的血量减少damage
void Enemy::enemyReduceHp(int damage)
{
    if(EHp>0){
        EHp-=damage;
    }
    else if(EHp<=0){
        EHp=0;
    }
}

//Enemy的血量增加heal
void Enemy::enemyIncreaseHp(int heal)
{
    if(EHp<EmaxHp){
        EHp+=heal;
    }
    else if(EHp>=EmaxHp){
        EHp=EmaxHp;
    }
}

void Enemy::enemyTurnToSoil()
{
    this->EDeath=Soil;
    goCount=1;
}

QPixmap Enemy::getpic(int i,int hp)
{
    QPixmap pic;
    if(hp>0){
        pic=Epics[i];
    }
    if(hp<=0){
        pic=EDeath;
    }
    return pic;
}
