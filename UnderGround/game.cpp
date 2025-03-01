#include "game.h"
#include "ui_game.h"
#include<qpainter.h>
#include<QTimerEvent>
#include<dia.h>
#include<dialog.h>
#include<diamop.h>
#include<diamarineboard.h>
#include<diavictory.h>
Game::Game(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Game)
{
    ui->setupUi(this);

    //游戏开始
    gameIsRunning=true;
    //初始化移动、转向、攻击、治疗的判定参数
    up=false;
    down=false;
    right=false;
    left=false;
    Diup=false;
    Didown=false;
    Dileft=false;
    Diright=false;
    attack=false;
    heal=false;
    //作弊码
    cheatCode=false;
    key1count=0;
    key2count1=0;
    key2count2=0;

    //初始化EGroup
    EGroup[0].Ex=100;EGroup[0].Ey=100;//Goblin1
    EGroup[1].Ex=200;EGroup[1].Ey=500;//Bokoblin1
    EGroup[2].Ex=700;EGroup[2].Ey=200;//Goblin2
    EGroup[3].Ex=1300;EGroup[3].Ey=300;//Goblin3
    EGroup[4].Ex=500;EGroup[4].Ey=800;//BokoBlin2

    //初始化武器模块
    LinkSword.load(":/Pictures/LinkSword.png");
    LinkSpear.load(":/Pictures/LinkSpear.png");
    LinkMop.load(":/Pictures/LinkMop.png");
    MasterSword.load(":/Pictures/MasterSword.png");//大师之剑
    BlueSpear.load(":/Pictures/BlueSpear.png");//古代兵装枪
    RedHeart.load(":/Pictures/Heart.png");//心心
    isChangeToSpear=false;
    isChangeToMop=false;
    isChangeToSword=true;
    Equiped=0;

    //初始化地图贴图
    //0泥土 1草 2石块 3宝箱关闭 4宝箱打开 5Goblin1
    //6Bokoblin1 7迷雾2 8迷雾3 9迷雾4 10绿色迷雾
    //11装备栏未选中 12装备栏选中 13林克背景图
    //14Goblin2 15Goblin3   16Bokoblin2
    //17Hole    18Mop     19Board   20MarineBoard  21DoorOpened 22Marine
    mapPic[0].load(":/Pictures/MapSoil.png");//泥土
    mapPic[1].load(":/Pictures/MapGrass2.png");//草
    mapPic[2].load(":/Pictures/MapStone.png");//石头
    mapPic[3].load(":/Pictures/MapChestClose.png");//宝箱关闭
    mapPic[4].load(":/Pictures/MapChestOpen.png");//宝箱打开
    mapPic[5].load(":/Pictures/GobFor.png");//Goblin1
    mapPic[14].load(":/Pictures/GobFor.png");//Goblin2
    mapPic[15].load(":/Pictures/GobFor.png");//Goblin3
    mapPic[6].load(":/Pictures/BokoBlinRight.png");//波克布林
    mapPic[16].load(":/Pictures/BokoBlinRight.png");//波克布林2
    mapPic[7].load(":/Pictures/MapFogSoil2.png");//战争迷雾2
    mapPic[8].load(":/Pictures/MapFogSoil3.jpg");//战争迷雾3
    mapPic[9].load(":/Pictures/MapFogSoil4.jpg");//战争迷雾4
    mapPic[10].load(":/Pictures/MapFog.png");//绿色战争迷雾
    mapPic[11].load(":/Pictures/MapEquipOff.png");//装备栏未选中
    mapPic[12].load(":/Pictures/MapEquipOn.png");//装备栏选中
    mapPic[13].load(":/Pictures/MapLinkBackGround.jpg");//林克背景图
    mapPic[17].load(":/Pictures/MapHole.png");//洞
    mapPic[18].load(":/Pictures/Mop.png");//拖把
    mapPic[19].load(":/Pictures/MapBoard.png");//路牌
    mapPic[20].load(":/Pictures/MapBoard.png");//马琳路牌
    mapPic[22].load(":/Pictures/Marine.png");//马琳
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
    connect(&timer,SIGNAL(timeout()),this,SLOT(UpdateHeroPos()));
    timer.start(70);
    connect(&Etim,SIGNAL(timeout()),this,SLOT(UpdateEnemys()));
    Etim.start(800);
}
Game::~Game()
{
    delete ui;
}

bool Game::enemyAllGo(Enemy *eg)
{
    int cou=0;
    int dc=0;
    for(int i=0;i<5;i++){
        if(eg[i].goCount==1){
            cou++;
        }
        if(eg[i].EHp<=0){
            dc++;
        }
    }
    if(cou==5&&dc==5){
        return true;
    }
    else return false;
}

//键盘按下操作
void Game::keyPressEvent(QKeyEvent *event){
    //移动
    if(event->key()==Qt::Key_W){
        up=true;
    }
    else if(event->key()==Qt::Key_S){
        down=true;
    }
    else if(event->key()==Qt::Key_D){
        right=true;
    }
    else if(event->key()==Qt::Key_A){
        left=true;
    }
    //转向
    else if(event->key()==Qt::Key_Up){
        Diup=true;
    }
    else if(event->key()==Qt::Key_Down){
        Didown=true;
    }
    else if(event->key()==Qt::Key_Right){
        Diright=true;
    }
    else if(event->key()==Qt::Key_Left){
        Dileft=true;
    }
    //Esc
    else if(event->key()==Qt::Key_Escape){
        gameIsRunning=false;
        Pause* pau=new Pause;
        pau->show();
        qDebug()<<"pressEsc";
    }
    //攻击
    else if(event->key()==Qt::Key_F){
        attack=true;
    }
    //治疗
    else if(event->key()==Qt::Key_R){
        heal=true;
    }
    //E键互动
    else if(event->key()==Qt::Key_E){
        if(thereHasChest()){
            Dia* chestOpen =new Dia;
            chestOpen->show();
            //Link->weapon=1;
            Link->hadSpear=true;
            if(!chestOpen->isActiveWindow())
                chestOpen->activateWindow();
        }
        if(thereHasBoard()){
            DiaBoard* board=new DiaBoard;
            board->show();
        }
        if(thereHasMarineBoard()){
            if(!enemyAllGo(EGroup)){
                DiaMarineBoard* mboard=new DiaMarineBoard;
                mboard->show();
            }
            else if(enemyAllGo(EGroup)){
                mapOne[11][7]=0;
                Link->mapOne[11][7]=0;
            }
        }
        if(thereHasMarine()){
            DiaVictory* vic=new DiaVictory;
            vic->show();
            this->close();

        }
    }
    //切换武器
    else if(event->key()==Qt::Key_Q){
        if(Link->weapon==0){
            if(Link->hadSpear){
                Link->weapon=1;
                isChangeToSword=false;
                isChangeToSpear=true;
            }
            else if(Link->hadSpear==false&&Link->hadMop==true){
                Link->weapon=2;
                isChangeToSword=false;
                isChangeToMop=true;
            }
        }
        else if(Link->weapon==1){
            if(Link->hadMop){
                Link->weapon=2;
                isChangeToSpear=false;
                isChangeToMop=true;
            }
            else{
                Link->weapon=0;
                isChangeToSpear=false;
                isChangeToSword=true;
            }
        }
        else if(Link->weapon==2){
            Link->weapon=0;
            isChangeToMop=false;
            isChangeToSword=true;
        }
    }
    //作弊码
    else if(event->key()==Qt::Key_2){
        if(key1count==3){
            key2count2++;
        }
        else key2count1++;
    }
    else if(event->key()==Qt::Key_1){
        if(key2count1==3){
            key1count++;
        }
    }
    return QWidget::keyPressEvent(event);
}

//键盘复位操作
void Game::keyReleaseEvent(QKeyEvent *event){
    //移动
    if(event->key()==Qt::Key_W){
        up=false;
    }
    else if(event->key()==Qt::Key_S){
        down=false;
    }
    else if(event->key()==Qt::Key_D){
        right=false;
    }
    else if(event->key()==Qt::Key_A){
        left=false;
    }
    //朝向
    else if(event->key()==Qt::Key_Up){
        Diup=false;
    }
    else if(event->key()==Qt::Key_Down){
        Didown=false;
    }
    else if(event->key()==Qt::Key_Right){
        Diright=false;
    }
    else if(event->key()==Qt::Key_Left){
        Dileft=false;
    }
    //Esc
    //攻击
    else if(event->key()==Qt::Key_F){
        attack=false;
    }
    //治疗
    else if(event->key()==Qt::Key_R){
        heal=false;
    }
    return QWidget::keyReleaseEvent(event);
}

void Game::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);//抗锯齿
    //绘制战争迷雾
    if(key2count2>=1){
        cheatCode=true;
    }
    if(cheatCode==false){
    for(int i=0;i<mapOne.size()-2;i++){
        for(int j=0;j<mapOne[0].size();j++){
            painter.drawPixmap(QRect(100*i,100*j,100,100),mapPic[10]);
        }
    }
    }
    if(cheatCode==true){
        for(int i=0;i<mapOne.size()-2;i++){
            for(int j=0;j<mapOne[0].size();j++){
                painter.drawPixmap(QRect(100*i,100*j,100,100),mapPic[mapOne[i][j]]);
            }
        }
    }
    //绘制装备栏
    for(int i=mapOne.size()-2;i<mapOne.size();i++){
        for(int j=0;j<9;j++){
            painter.drawPixmap(QRect(100*i,100*j,100,100),mapPic[mapOne[i][j]]);
        }
    }
    //绘制mapOne
    for(int i=0;i<mapOne.size()-2;i++){
        if(i==(Link->x)/100||i==(Link->x)/100-1||i==(Link->x)/100+1||i==(Link->x)/100+2||i==(Link->x)/100-2){
            for(int j=0;j<mapOne[0].size();j++){
                if((Link->direction==0)){//下
                    if(i==(Link->x)/100+1||i==(Link->x)/100-1||i==(Link->x)/100){
                        if(j==(Link->y)/100||((j==(Link->y)/100+1)&&i==((Link->x)/100))||((j==(Link->y)/100+2)&&i==((Link->x)/100))){
                            painter.drawPixmap(QRect(100*i,100*j,100,100),mapPic[0]);//将底图设置为泥土
                            //绘制哥布林
                            if(mapOne[i][j]==5){
                                painter.drawPixmap(QRect(EGroup[0].Ex,EGroup[0].Ey,EGroup[0].Ewid,EGroup[0].Ehei),EGroup[0].getpic(0,EGroup[0].EHp));
                                //绘制血条
                                if(EGroup[0].EHp>0){
                                    QBrush red_brush(QColor("#F20900"));//把刷子设置为红色
                                    painter.setBrush(red_brush);//应用刷子
                                    float rate=(float(EGroup[0].EHp))/(float(EGroup[0].EmaxHp));
                                    painter.drawRect(EGroup[0].Ex,EGroup[0].Ey,rate*(float(EGroup[0].Ewid)),EGroup[0].Ehei*0.1);//绘制矩形
                                }
                            }
                            else if(mapOne[i][j]==14){
                                painter.drawPixmap(QRect(EGroup[2].Ex,EGroup[2].Ey,EGroup[2].Ewid,EGroup[2].Ehei),EGroup[2].getpic(2,EGroup[2].EHp));
                                //绘制血条
                                if(EGroup[2].EHp>0){
                                    QBrush red_brush(QColor("#F20900"));//把刷子设置为红色
                                    painter.setBrush(red_brush);//应用刷子
                                    float rate=(float(EGroup[2].EHp))/(float(EGroup[2].EmaxHp));
                                    painter.drawRect(EGroup[2].Ex,EGroup[2].Ey,rate*(float(EGroup[2].Ewid)),EGroup[2].Ehei*0.1);//绘制矩形
                                }
                            }
                            else if(mapOne[i][j]==15){
                                painter.drawPixmap(QRect(EGroup[3].Ex,EGroup[3].Ey,EGroup[3].Ewid,EGroup[3].Ehei),EGroup[3].getpic(3,EGroup[3].EHp));
                                //绘制血条
                                if(EGroup[3].EHp>0){
                                    QBrush red_brush(QColor("#F20900"));//把刷子设置为红色
                                    painter.setBrush(red_brush);//应用刷子
                                    float rate=(float(EGroup[3].EHp))/(float(EGroup[3].EmaxHp));
                                    painter.drawRect(EGroup[3].Ex,EGroup[3].Ey,rate*(float(EGroup[3].Ewid)),EGroup[3].Ehei*0.1);//绘制矩形
                                }
                            }
                            //绘制波克布林
                            else if(mapOne[i][j]==6){
                                painter.drawPixmap(QRect(EGroup[1].Ex,EGroup[1].Ey,EGroup[1].Ewid,EGroup[1].Ehei),EGroup[1].getpic(1,EGroup[1].EHp));
                                //绘制血条
                                if(EGroup[1].EHp>0){
                                    QBrush red_brush(QColor("#F20900"));//把刷子设置为红色
                                    painter.setBrush(red_brush);//应用刷子
                                    float rate=(float(EGroup[1].EHp))/(float(EGroup[1].EmaxHp));
                                    painter.drawRect(EGroup[1].Ex,EGroup[1].Ey,rate*(float(EGroup[1].Ewid)),EGroup[1].Ehei*0.1);//绘制矩形
                                }
                            }
                            else if(mapOne[i][j]==16){
                                painter.drawPixmap(QRect(EGroup[4].Ex,EGroup[4].Ey,EGroup[4].Ewid,EGroup[4].Ehei),EGroup[4].getpic(4,EGroup[4].EHp));
                                //绘制血条
                                if(EGroup[4].EHp>0){
                                    QBrush red_brush(QColor("#F20900"));//把刷子设置为红色
                                    painter.setBrush(red_brush);//应用刷子
                                    float rate=(float(EGroup[4].EHp))/(float(EGroup[4].EmaxHp));
                                    painter.drawRect(EGroup[4].Ex,EGroup[4].Ey,rate*(float(EGroup[4].Ewid)),EGroup[4].Ehei*0.1);//绘制矩形
                                }
                            }
                            else painter.drawPixmap(QRect(100*i,100*j,100,100),mapPic[mapOne[i][j]]);//绘制第二层贴图
                        }
                    }
                }
                else if(Link->direction==1){//上
                    if(i==(Link->x)/100+1||i==(Link->x)/100-1||i==(Link->x)/100){
                        if(j==(Link->y)/100||((j==(Link->y)/100-1)&&i==((Link->x)/100))||((j==(Link->y)/100-2)&&i==((Link->x)/100))){
                            painter.drawPixmap(QRect(100*i,100*j,100,100),mapPic[0]);//将底图设置为泥土
                            //绘制哥布林
                                if(mapOne[i][j]==5){
                                    painter.drawPixmap(QRect(EGroup[0].Ex,EGroup[0].Ey,EGroup[0].Ewid,EGroup[0].Ehei),EGroup[0].getpic(0,EGroup[0].EHp));
                                    //绘制血条
                                    if(EGroup[0].EHp>0){
                                        QBrush red_brush(QColor("#F20900"));//把刷子设置为红色
                                        painter.setBrush(red_brush);//应用刷子
                                        float rate=(float(EGroup[0].EHp))/(float(EGroup[0].EmaxHp));
                                        painter.drawRect(EGroup[0].Ex,EGroup[0].Ey,rate*(float(EGroup[0].Ewid)),EGroup[0].Ehei*0.1);//绘制矩形
                                    }
                                }
                                else if(mapOne[i][j]==14){
                                    painter.drawPixmap(QRect(EGroup[2].Ex,EGroup[2].Ey,EGroup[2].Ewid,EGroup[2].Ehei),EGroup[2].getpic(2,EGroup[2].EHp));
                                    //绘制血条
                                    if(EGroup[2].EHp>0){
                                        QBrush red_brush(QColor("#F20900"));//把刷子设置为红色
                                        painter.setBrush(red_brush);//应用刷子
                                        float rate=(float(EGroup[2].EHp))/(float(EGroup[2].EmaxHp));
                                        painter.drawRect(EGroup[2].Ex,EGroup[2].Ey,rate*(float(EGroup[2].Ewid)),EGroup[2].Ehei*0.1);//绘制矩形
                                    }
                                }
                                else if(mapOne[i][j]==15){
                                    painter.drawPixmap(QRect(EGroup[3].Ex,EGroup[3].Ey,EGroup[3].Ewid,EGroup[3].Ehei),EGroup[3].getpic(3,EGroup[3].EHp));
                                    //绘制血条
                                    if(EGroup[3].EHp>0){
                                        QBrush red_brush(QColor("#F20900"));//把刷子设置为红色
                                        painter.setBrush(red_brush);//应用刷子
                                        float rate=(float(EGroup[3].EHp))/(float(EGroup[3].EmaxHp));
                                        painter.drawRect(EGroup[3].Ex,EGroup[3].Ey,rate*(float(EGroup[3].Ewid)),EGroup[3].Ehei*0.1);//绘制矩形
                                    }
                                }
                                //绘制波克布林
                                else if(mapOne[i][j]==6){
                                    painter.drawPixmap(QRect(EGroup[1].Ex,EGroup[1].Ey,EGroup[1].Ewid,EGroup[1].Ehei),EGroup[1].getpic(1,EGroup[1].EHp));
                                    //绘制血条
                                    if(EGroup[1].EHp>0){
                                        QBrush red_brush(QColor("#F20900"));//把刷子设置为红色
                                        painter.setBrush(red_brush);//应用刷子
                                        float rate=(float(EGroup[1].EHp))/(float(EGroup[1].EmaxHp));
                                        painter.drawRect(EGroup[1].Ex,EGroup[1].Ey,rate*(float(EGroup[1].Ewid)),EGroup[1].Ehei*0.1);//绘制矩形
                                    }
                                }
                                else if(mapOne[i][j]==16){
                                    painter.drawPixmap(QRect(EGroup[4].Ex,EGroup[4].Ey,EGroup[4].Ewid,EGroup[4].Ehei),EGroup[4].getpic(4,EGroup[4].EHp));
                                    //绘制血条
                                    if(EGroup[4].EHp>0){
                                        QBrush red_brush(QColor("#F20900"));//把刷子设置为红色
                                        painter.setBrush(red_brush);//应用刷子
                                        float rate=(float(EGroup[4].EHp))/(float(EGroup[4].EmaxHp));
                                        painter.drawRect(EGroup[4].Ex,EGroup[4].Ey,rate*(float(EGroup[4].Ewid)),EGroup[4].Ehei*0.1);//绘制矩形
                                    }
                                }
                                else painter.drawPixmap(QRect(100*i,100*j,100,100),mapPic[mapOne[i][j]]);//绘制第二层贴图
                            }
                        }
                    }
                    else if(Link->direction==2){//左
                        if(i==(Link->x)/100-1||i==(Link->x)/100-2||i==(Link->x)/100){
                            if(((j==(Link->y)/100)&&i==((Link->x)/100-1))||((j==(Link->y)/100)&&i==((Link->x)/100-2))||
                                    ((j==(Link->y)/100)&&i==((Link->x)/100))||((j==(Link->y)/100-1)&&i==((Link->x)/100))||((j==(Link->y)/100+1)&&i==((Link->x)/100))){
                                painter.drawPixmap(QRect(100*i,100*j,100,100),mapPic[0]);//将底图设置为泥土
                                if(mapOne[i][j]==5){
                                    painter.drawPixmap(QRect(EGroup[0].Ex,EGroup[0].Ey,EGroup[0].Ewid,EGroup[0].Ehei),EGroup[0].getpic(0,EGroup[0].EHp));
                                    //绘制血条
                                    if(EGroup[0].EHp>0){
                                        QBrush red_brush(QColor("#F20900"));//把刷子设置为红色
                                        painter.setBrush(red_brush);//应用刷子
                                        float rate=(float(EGroup[0].EHp))/(float(EGroup[0].EmaxHp));
                                        painter.drawRect(EGroup[0].Ex,EGroup[0].Ey,rate*(float(EGroup[0].Ewid)),EGroup[0].Ehei*0.1);//绘制矩形
                                    }
                                }
                                else if(mapOne[i][j]==14){
                                    painter.drawPixmap(QRect(EGroup[2].Ex,EGroup[2].Ey,EGroup[2].Ewid,EGroup[2].Ehei),EGroup[2].getpic(2,EGroup[2].EHp));
                                    //绘制血条
                                    if(EGroup[2].EHp>0){
                                        QBrush red_brush(QColor("#F20900"));//把刷子设置为红色
                                        painter.setBrush(red_brush);//应用刷子
                                        float rate=(float(EGroup[2].EHp))/(float(EGroup[2].EmaxHp));
                                        painter.drawRect(EGroup[2].Ex,EGroup[2].Ey,rate*(float(EGroup[2].Ewid)),EGroup[2].Ehei*0.1);//绘制矩形
                                    }
                                }
                                else if(mapOne[i][j]==15){
                                    painter.drawPixmap(QRect(EGroup[3].Ex,EGroup[3].Ey,EGroup[3].Ewid,EGroup[3].Ehei),EGroup[3].getpic(3,EGroup[3].EHp));
                                    //绘制血条
                                    if(EGroup[3].EHp>0){
                                        QBrush red_brush(QColor("#F20900"));//把刷子设置为红色
                                        painter.setBrush(red_brush);//应用刷子
                                        float rate=(float(EGroup[3].EHp))/(float(EGroup[3].EmaxHp));
                                        painter.drawRect(EGroup[3].Ex,EGroup[3].Ey,rate*(float(EGroup[3].Ewid)),EGroup[3].Ehei*0.1);//绘制矩形
                                    }
                                }
                                //绘制波克布林
                                else if(mapOne[i][j]==6){
                                    painter.drawPixmap(QRect(EGroup[1].Ex,EGroup[1].Ey,EGroup[1].Ewid,EGroup[1].Ehei),EGroup[1].getpic(1,EGroup[1].EHp));
                                    //绘制血条
                                    if(EGroup[1].EHp>0){
                                        QBrush red_brush(QColor("#F20900"));//把刷子设置为红色
                                        painter.setBrush(red_brush);//应用刷子
                                        float rate=(float(EGroup[1].EHp))/(float(EGroup[1].EmaxHp));
                                        painter.drawRect(EGroup[1].Ex,EGroup[1].Ey,rate*(float(EGroup[1].Ewid)),EGroup[1].Ehei*0.1);//绘制矩形
                                    }
                                }
                                else if(mapOne[i][j]==16){
                                    painter.drawPixmap(QRect(EGroup[4].Ex,EGroup[4].Ey,EGroup[4].Ewid,EGroup[4].Ehei),EGroup[4].getpic(4,EGroup[4].EHp));
                                    //绘制血条
                                    if(EGroup[4].EHp>0){
                                        QBrush red_brush(QColor("#F20900"));//把刷子设置为红色
                                        painter.setBrush(red_brush);//应用刷子
                                        float rate=(float(EGroup[4].EHp))/(float(EGroup[4].EmaxHp));
                                        painter.drawRect(EGroup[4].Ex,EGroup[4].Ey,rate*(float(EGroup[4].Ewid)),EGroup[4].Ehei*0.1);//绘制矩形
                                    }
                                }
                                else painter.drawPixmap(QRect(100*i,100*j,100,100),mapPic[mapOne[i][j]]);//绘制第二层贴图
                            }
                        }
                    }
                    else if(Link->direction==3){//右
                        if(i==(Link->x)/100+1||i==(Link->x)/100+2||i==(Link->x)/100){
                            if(((j==(Link->y)/100)&&i==((Link->x)/100+2))||((j==(Link->y)/100)&&i==((Link->x)/100+1))
                                    ||((j==(Link->y)/100)&&i==((Link->x)/100))||((j==(Link->y)/100+1)&&i==((Link->x)/100))||((j==(Link->y)/100-1)&&i==((Link->x)/100))){
                                painter.drawPixmap(QRect(100*i,100*j,100,100),mapPic[0]);//将底图设置为泥土
                                if(mapOne[i][j]==5){
                                    painter.drawPixmap(QRect(EGroup[0].Ex,EGroup[0].Ey,EGroup[0].Ewid,EGroup[0].Ehei),EGroup[0].getpic(EGroup[0].Edirection,EGroup[0].EHp));
                                    //绘制血条
                                    if(EGroup[0].EHp>0){
                                        QBrush red_brush(QColor("#F20900"));//把刷子设置为红色
                                        painter.setBrush(red_brush);//应用刷子
                                        float rate=(float(EGroup[0].EHp))/(float(EGroup[0].EmaxHp));
                                        painter.drawRect(EGroup[0].Ex,EGroup[0].Ey,rate*(float(EGroup[0].Ewid)),EGroup[0].Ehei*0.1);//绘制矩形
                                    }
                                }
                                else if(mapOne[i][j]==14){
                                    painter.drawPixmap(QRect(EGroup[2].Ex,EGroup[2].Ey,EGroup[2].Ewid,EGroup[2].Ehei),EGroup[2].getpic(2,EGroup[2].EHp));
                                    //绘制血条
                                    if(EGroup[2].EHp>0){
                                        QBrush red_brush(QColor("#F20900"));//把刷子设置为红色
                                        painter.setBrush(red_brush);//应用刷子
                                        float rate=(float(EGroup[2].EHp))/(float(EGroup[2].EmaxHp));
                                        painter.drawRect(EGroup[2].Ex,EGroup[2].Ey,rate*(float(EGroup[2].Ewid)),EGroup[2].Ehei*0.1);//绘制矩形
                                    }
                                }
                                else if(mapOne[i][j]==15){
                                    painter.drawPixmap(QRect(EGroup[3].Ex,EGroup[3].Ey,EGroup[3].Ewid,EGroup[3].Ehei),EGroup[3].getpic(3,EGroup[3].EHp));
                                    //绘制血条
                                    if(EGroup[3].EHp>0){
                                        QBrush red_brush(QColor("#F20900"));//把刷子设置为红色
                                        painter.setBrush(red_brush);//应用刷子
                                        float rate=(float(EGroup[3].EHp))/(float(EGroup[3].EmaxHp));
                                        painter.drawRect(EGroup[3].Ex,EGroup[3].Ey,rate*(float(EGroup[3].Ewid)),EGroup[3].Ehei*0.1);//绘制矩形
                                    }
                                }
                                //绘制波克布林
                                else if(mapOne[i][j]==6){
                                    painter.drawPixmap(QRect(EGroup[1].Ex,EGroup[1].Ey,EGroup[1].Ewid,EGroup[1].Ehei),EGroup[1].getpic(1,EGroup[1].EHp));
                                    //绘制血条
                                    if(EGroup[1].EHp>0){
                                        QBrush red_brush(QColor("#F20900"));//把刷子设置为红色
                                        painter.setBrush(red_brush);//应用刷子
                                        float rate=(float(EGroup[1].EHp))/(float(EGroup[1].EmaxHp));
                                        painter.drawRect(EGroup[1].Ex,EGroup[1].Ey,rate*(float(EGroup[1].Ewid)),EGroup[1].Ehei*0.1);//绘制矩形
                                    }
                                }
                                else if(mapOne[i][j]==16){
                                    painter.drawPixmap(QRect(EGroup[4].Ex,EGroup[4].Ey,EGroup[4].Ewid,EGroup[4].Ehei),EGroup[4].getpic(4,EGroup[4].EHp));
                                    //绘制血条
                                    if(EGroup[4].EHp>0){
                                        QBrush red_brush(QColor("#F20900"));//把刷子设置为红色
                                        painter.setBrush(red_brush);//应用刷子
                                        float rate=(float(EGroup[4].EHp))/(float(EGroup[4].EmaxHp));
                                        painter.drawRect(EGroup[4].Ex,EGroup[4].Ey,rate*(float(EGroup[4].Ewid)),EGroup[4].Ehei*0.1);//绘制矩形
                                    }
                                }
                                else painter.drawPixmap(QRect(100*i,100*j,100,100),mapPic[mapOne[i][j]]);//绘制第二层贴图
                            }
                        }
                    }
                }
            }
        }

    //绘制Hero
    painter.drawPixmap(QRect(Link->getX(),Link->getY(),Link->getWid(),Link->getHei()),Link->getpic(Link->direction));
    //绘制装备栏
    if(Link->weapon==0){
        painter.drawPixmap(QRect(1400,0,100,100),mapPic[12]);
    }
    else if(Link->weapon==1){
        painter.drawPixmap(QRect(1500,0,100,100),mapPic[12]);
    }
    else if(Link->weapon==2){
        painter.drawPixmap(QRect(1400,100,100,100),mapPic[12]);
    }
    //绘制武器
    painter.drawPixmap(QRect(1400,0,100,100),MasterSword);
    if(Link->hadSpear){
        painter.drawPixmap(QRect(1500,0,100,100),BlueSpear);
    }
    if(Link->hadMop){
        painter.drawPixmap(QRect(1400,100,100,100),mapPic[18]);
    }
    if(isChangeToSpear){
        painter.drawPixmap(QRect(1400,220,200,250),LinkSpear);
    }
    else if(isChangeToSword){
        painter.drawPixmap(QRect(1400,220,200,250),LinkSword);
    }
    else if(isChangeToMop){
        painter.drawPixmap(QRect(1400,220,180,250),LinkMop);
    }
    if(mapOne[Link->x/100][Link->y/100]==18&&Link->hadMop==false){
        int i=Link->x/100;int j=Link->y/100;
        mapOne[i][j]=0;
        Link->hadMop=true;
        showDiaMop();
    }
    //绘制血条
    for(int i=0;i<Link->Hp;i++){
        painter.drawPixmap(QRect(1400+i*40,500,25,25),RedHeart);
    }
    if(Link->Hp<=0){
        Dialog* gameover=new Dialog;
        gameover->show();
        this->close();
    }
}
    bool Game::thereHasChest(){
        switch (Link->direction) {
        //下方
        case 0:
            if(mapOne[(Link->x)/100][(Link->y)/100+1]==3){
                //qDebug()<<"chest";
                mapOne[(Link->x)/100][(Link->y)/100+1]=4;
                return true;
            }
            else return false;
            break;
            //上方
        case 1:
            if(mapOne[(Link->x)/100][(Link->y)/100-1]==3){
                mapOne[(Link->x)/100][(Link->y)/100-1]=4;
                return true;
            }
            else return false;
            break;
            //左
        case 2:
            if(mapOne[(Link->x)/100-1][(Link->y)/100]==3){
                mapOne[(Link->x)/100-1][(Link->y)/100]=4;
                return true;
            }
            else return false;
            break;
            //右
        case 3:
            if(mapOne[(Link->x)/100+1][(Link->y)/100]==3){
                mapOne[(Link->x)/100+1][(Link->y)/100]=4;
                return true;
            }
            else return false;
            break;
        }

    }

    bool Game::thereHasBoard()
    {
        switch (Link->direction) {
        //下方
        case 0:
            if(mapOne[(Link->x)/100][(Link->y)/100+1]==19){
                return true;
            }
            else return false;
            break;
            //上方
        case 1:
            if(mapOne[(Link->x)/100][(Link->y)/100-1]==19){
                return true;
            }
            else return false;
            break;
            //左
        case 2:
            if(mapOne[(Link->x)/100-1][(Link->y)/100]==19){
                return true;
            }
            else return false;
            break;
            //右
        case 3:
            if(mapOne[(Link->x)/100+1][(Link->y)/100]==19){
                return true;
            }
            else return false;
            break;
        }
    }

    bool Game::thereHasMarineBoard()
    {
        switch (Link->direction) {
        //下方
        case 0:
            if(mapOne[(Link->x)/100][(Link->y)/100+1]==20){
                return true;
            }
            else return false;
            break;
            //上方
        case 1:
            if(mapOne[(Link->x)/100][(Link->y)/100-1]==20){
                return true;
            }
            else return false;
            break;
            //左
        case 2:
            if(mapOne[(Link->x)/100-1][(Link->y)/100]==20){
                return true;
            }
            else return false;
            break;
            //右
        case 3:
            if(mapOne[(Link->x)/100+1][(Link->y)/100]==20){
                return true;
            }
            else return false;
            break;
        }
    }

    bool Game::thereHasMarine()
    {
        switch (Link->direction) {
        //下方
        case 0:
            if(mapOne[(Link->x)/100][(Link->y)/100+1]==22){
                return true;
            }
            else return false;
            break;
            //上方
        case 1:
            if(mapOne[(Link->x)/100][(Link->y)/100-1]==22){
                return true;
            }
            else return false;
            break;
            //左
        case 2:
            if(mapOne[(Link->x)/100-1][(Link->y)/100]==22){
                return true;
            }
            else return false;
            break;
            //右
        case 3:
            if(mapOne[(Link->x)/100+1][(Link->y)/100]==22){
                return true;
            }
            else return false;
            break;
        }
    }

    void Game::EnemyAttack()
    {
        if(Link->heroIsIn(EGroup[0].Ex-101,EGroup[0].Ex-1,EGroup[0].Ey-1,EGroup[0].Ey+1)){
            if(EGroup[0].EHp>0){
                Link->heroReduceHp(1);
            }
        }
        if(Link->heroIsIn(EGroup[2].Ex-101,EGroup[2].Ex-1,EGroup[2].Ey-1,EGroup[2].Ey+1)){
            if(EGroup[2].EHp>0){
                Link->heroReduceHp(1);
            }
        }
        if(Link->heroIsIn(EGroup[3].Ex-101,EGroup[3].Ex-1,EGroup[3].Ey-1,EGroup[3].Ey+1)){
            if(EGroup[3].EHp>0){
                Link->heroReduceHp(1);
            }
        }
        if(Link->heroIsIn(EGroup[1].Ex+1,EGroup[1].Ex+101,EGroup[1].Ey-1,EGroup[1].Ey+1)){
            if(EGroup[1].EHp>0){
                Link->heroReduceHp(1);
            }
        }
        if(Link->heroIsIn(EGroup[4].Ex+1,EGroup[4].Ex+101,EGroup[4].Ey-1,EGroup[4].Ey+1)){
            if(EGroup[4].EHp>0){
                Link->heroReduceHp(1);
            }
        }

    }

    void Game::showDiaMop()
    {
        DiaMop* mop=new DiaMop;
        up=right=left=down=false;
        mop->show();
    }

    void Game::UpdateEnemys()
    {
        EnemyAttack();
    }

    void Game::UpdateHeroPos()
    {
        Link->heroMove(up,down,left,right);
        Link->heroTrun(Diup,Didown,Dileft,Diright);
        for(int i=0;i<5;i++){
            Link->heroAttack(attack,Link->weapon,&EGroup[i]);
            Link->heroHeal(heal,&EGroup[i]);
        }
        update();
    }
