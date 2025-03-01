#include "hero.h"
#define Chao_1 ":/Pictures/LinkForward.png"
Hero::Hero(QWidget *parent) : QWidget(parent)
{
    //初始化人物属性
    this->Hp=5;
    this->maxHp=5;
    this->En=100;
    this->wid=100;
    this->hei=100;
    this->x=0;
    this->y=0;
    direction=0;
    weapon=0;
    hadSpear=false;
    hadMop=false;
    ChaoXiang[0].load(QString(":/Pictures/LinkForward.png").arg(1));
    ChaoXiang[1].load(QString(":/Pictures/LinkBac.png").arg(2));
    ChaoXiang[2].load(QString(":/Pictures/LinkLeft.png").arg(3));
    ChaoXiang[3].load(QString(":/Pictures/LinkRight.png").arg(4));
    //将mapOne初始化为(14+2)x(9+2)的二维数组
    mapOne.resize(16);
    for(int i=0;i<mapOne.size();i++){
        mapOne[i].resize(11);
    }
    //给mapOne赋初始值（设置Soil）
    for(int i=0;i<mapOne.size();i++){
        for(int j=0;j<mapOne[0].size();j++){
            mapOne[i][j]=0;
        }
    }
    //设置Stone
    mapOne[0][2]=2;mapOne[4][0]=2;mapOne[7][1]=2;mapOne[1][7]=2;mapOne[3][8]=2;mapOne[4][7]=2;mapOne[4][6]=2;
    mapOne[9][7]=2;mapOne[10][6]=2;mapOne[10][8]=2;mapOne[7][1]=2;mapOne[6][1]=2;
    //设置Grass
    mapOne[3][0]=1;mapOne[1][3]=1;mapOne[5][6]=1;mapOne[6][4]=1;mapOne[9][3]=1;mapOne[11][6]=1;mapOne[12][0]=1;
    //设置BlueSpear宝箱
    mapOne[4][8]=3;
    //设置拖把
    mapOne[8][0]=18;
    //设置洞
    mapOne[13][2]=17;mapOne[13][4]=17;mapOne[12][3]=17;
    //设置路牌
    mapOne[2][3]=19;
    //设置Bokoblin
    mapOne[2][5]=6;//1
    mapOne[5][8]=16;//2
    //设置Goblin
    mapOne[1][1]=5;//1
    mapOne[7][2]=14;//2
    mapOne[13][3]=15;//3
    //设置公主马琳
    mapOne[10][7]=22;
    //设置马琳路牌
    mapOne[11][7]=20;
    //设置装备栏
    mapOne[14][0]=11;mapOne[14][1]=11;mapOne[15][0]=11;mapOne[15][1]=11;
    for(int i=14;i<16;i++){
        for(int j=2;j<9;j++){
            mapOne[i][j]=13;
        }
    }
}

bool Hero::heroIsIn(int left, int right, int up, int down)
{
    if(this->x<=right&&this->x>=left&&this->y<=down&&this->y>=up){
        return true;
    }
    else return false;
}

bool Hero::heroIsInPoint(int xx, int yy)
{
    if(x==xx&&y==yy)
        return true;
    else return false;
}

bool Hero::heroIsInMap(QVector< QVector<int> > map)
{
    switch(direction){
    case 0://下
        if(y==800)
            return true;
        else if(map[x/100][y/100+1]==2||map[x/100][y/100+1]==3||map[x/100][y/100+1]==4
                ||map[x/100][y/100+1]==5||map[x/100][y/100+1]==6||map[x/100][y/100+1]==14
                ||map[x/100][y/100+1]==15||map[x/100][y/100+1]==16||map[x/100][y/100+1]==17
                ||map[x/100][y/100+1]==19||map[x/100][y/100+1]==22||map[x/100][y/100+1]==20)
            return false;
        else return true;
            break;
    case 1://上
        if(y==0)
            return true;
        if(map[x/100][y/100-1]==2||map[x/100][y/100-1]==3||map[x/100][y/100-1]==4
                ||map[x/100][y/100-1]==5||map[x/100][y/100-1]==6||map[x/100][y/100-1]==14
                ||map[x/100][y/100-1]==15||map[x/100][y/100-1]==16||map[x/100][y/100-1]==17
                ||map[x/100][y/100-1]==19||map[x/100][y/100-1]==22||map[x/100][y/100-1]==20)
            return false;
        else return true;
        break;
    case 2://左
        if(x==0)
            return true;
        else if(map[x/100-1][y/100]==2||map[x/100-1][y/100]==3||map[x/100-1][y/100]==4
                ||map[x/100-1][y/100]==5||map[x/100-1][y/100]==6||map[x/100-1][y/100]==14
                ||map[x/100-1][y/100]==15||map[x/100-1][y/100]==16||map[x/100-1][y/100]==17
                ||map[x/100-1][y/100]==19||map[x/100-1][y/100]==22||map[x/100-1][y/100]==20)
            return false;
        else return true;
        break;
    case 3://右
        if(map[x/100+1][y/100]==2||map[x/100+1][y/100]==3||map[x/100+1][y/100]==4
                ||map[x/100+1][y/100]==5||map[x/100+1][y/100]==6||map[x/100+1][y/100]==14
                ||map[x/100+1][y/100]==15||map[x/100+1][y/100]==16||map[x/100+1][y/100]==17
                ||map[x/100+1][y/100]==19||map[x/100+1][y/100]==22||map[x/100+1][y/100]==20)
            return false;
        else return true;
        break;
    }
    return true;
}

//Hero移动函数
void Hero::heroMove(bool up, bool down, bool left, bool right)
{
    if(heroIsInMap(mapOne)){
        if(up){
            if(y>0){
                if(direction==1){
                    for(int i=0;i<100;i++)
                        y-=1;
                }
            }
        }
        else if(down){
            if(y<800){
                if(direction==0){
                    this->y+=100;
                }
            }
        }
        else if(left){
            if(x>0){
                if(direction==2){
                    this->x-=100;
                }
            }
        }
        else if(right){
            if(x<1300){
                if(direction==3){
                    this->x+=100;
                }
            }
        }
    }
}

//浅浅实现一些get函数
int Hero::getX(){
    return this->x;
}
int Hero::getY(){
    return this->y;
}
int Hero::getHp(){
    return this->Hp;
}
int Hero::getEn(){
    return this->En;
}

//获取英雄图片
QPixmap Hero::getpic(int i)
{
    QPixmap pic;
    pic=ChaoXiang[i];
    return pic;
}

//英雄攻击
void Hero::heroAttack(bool b,int weap,Enemy* Gob)
{
    if(b){
    //weapon0:剑(普通)
    if(weap==0){
            //qDebug()<<direction<<Gob->Ex<<Gob->Ey<<x<<y;
            switch (direction) {
            //下方
            case 0:
                if(Gob->enemyIsIn((this->x)-10,(this->x)+10,(this->y)+90,(this->y)+110)){
                    Gob->enemyReduceHp(50);
                }
            break;
            //上方
            case 1:
                if(Gob->enemyIsIn((this->x)-10,(this->x)+10,(this->y)-110,(this->y)-90))
                    Gob->enemyReduceHp(50);
            break;
            //左
            case 2:
                if(Gob->enemyIsIn((this->x)-110,(this->x)-90,(this->y)-10,(this->y)+10))
                    Gob->enemyReduceHp(50);
            break;
            //右
            case 3:
                if(Gob->enemyIsIn((this->x)+90,(this->x)+110,(this->y)-10,(this->y)+10))
                    Gob->enemyReduceHp(50);
            break;

            }
        }
    if(weap==1){//矛
        //qDebug()<<direction<<Gob->Ex<<Gob->Ey<<x<<y;
        switch (direction) {
        //下方
        case 0:
            if(Gob->enemyIsIn((this->x)-10,(this->x)+10,(this->y)+90,(this->y)+110)
                    ||Gob->enemyIsIn((this->x)-10,(this->x)+10,(this->y)+110,(this->y)+210)){
                Gob->enemyReduceHp(30);
            }
            break;
            //上方
        case 1:
            if(Gob->enemyIsIn((this->x)-10,(this->x)+10,(this->y)-110,(this->y)-90)||
                    Gob->enemyIsIn((this->x)-10,(this->x)+10,(this->y)-210,(this->y)-110))
                Gob->enemyReduceHp(30);
            break;
            //左
        case 2:
            if(Gob->enemyIsIn((this->x)-110,(this->x)-90,(this->y)-10,(this->y)+10)||
                    Gob->enemyIsIn((this->x)-210,(this->x)-110,(this->y)-10,(this->y)+10))
                Gob->enemyReduceHp(30);
            break;
            //右
        case 3:
            if(Gob->enemyIsIn((this->x)+90,(this->x)+110,(this->y)-10,(this->y)+10)||
                    Gob->enemyIsIn((this->x)+110,(this->x)+210,(this->y)-10,(this->y)+10))
                Gob->enemyReduceHp(30);
            break;

        }
    }
    if(weap==2){//拖把
        if(Gob->EHp<=0){
            switch (direction){
            //下方
            case 0:
                if(Gob->enemyIsIn((this->x)-10,(this->x)+10,(this->y)+90,(this->y)+110)
                        ||Gob->enemyIsIn((this->x)-10,(this->x)+10,(this->y)+110,(this->y)+210)){
                    mapOne[Gob->Ex/100][Gob->Ey/100]=0;
                    Gob->enemyTurnToSoil();
                }
                break;
                //上方
            case 1:
                if(Gob->enemyIsIn((this->x)-10,(this->x)+10,(this->y)-110,(this->y)-90)||
                        Gob->enemyIsIn((this->x)-10,(this->x)+10,(this->y)-210,(this->y)-110)){
                    mapOne[Gob->Ex/100][Gob->Ey/100]=0;
                    Gob->enemyTurnToSoil();
                }
                break;
                //左
            case 2:
                if(Gob->enemyIsIn((this->x)-110,(this->x)-90,(this->y)-10,(this->y)+10)||
                        Gob->enemyIsIn((this->x)-210,(this->x)-110,(this->y)-10,(this->y)+10)){
                    mapOne[Gob->Ex/100][Gob->Ey/100]=0;
                    Gob->enemyTurnToSoil();
                }
                break;
                //右
            case 3:
                if(Gob->enemyIsIn((this->x)+90,(this->x)+110,(this->y)-10,(this->y)+10)||
                        Gob->enemyIsIn((this->x)+110,(this->x)+210,(this->y)-10,(this->y)+10)){
                    mapOne[Gob->Ex/100][Gob->Ey/100]=0;
                    Gob->enemyTurnToSoil();
                }
                break;
            }
        }
    }
    }
}

void Hero::heroHeal(bool healIsTrue, Enemy * Gob)
{
    if(healIsTrue){
        switch (direction) {
        //下方
        case 0:
            if(Gob->enemyIsIn((this->x)-10,(this->x)+10,(this->y)+90,(this->y)+110)){
                Gob->enemyIncreaseHp(50);
            }
        break;
        //上方
        case 1:
            if(Gob->enemyIsIn((this->x)-10,(this->x)+10,(this->y)-110,(this->y)-90))
                Gob->enemyIncreaseHp(50);
        break;
        //左
        case 2:
            if(Gob->enemyIsIn((this->x)-110,(this->x)-90,(this->y)-10,(this->y)+10))
                Gob->enemyIncreaseHp(50);
        break;
        //右
        case 3:
            if(Gob->enemyIsIn((this->x)+90,(this->x)+110,(this->y)-10,(this->y)+10))
                Gob->enemyIncreaseHp(50);
        break;
        }
    }
}

//英雄扣血
void Hero::heroReduceHp(int damage)
{
    if(Hp>0){
        Hp-=damage;
    }
    else if(Hp<=0){
        Hp=0;
    }
}

//英雄转向
void Hero::heroTrun(bool up, bool down, bool left, bool right)
{
    if(down){
        this->direction=0;
    }
    else if(up){
        this->direction=1;
    }
    else if(left){
        this->direction=2;
    }
    else if(right){
        this->direction=3;
    }
}
int Hero::getWid(){
    return this->wid;
}
int Hero::getHei(){
    return this->hei;
}
