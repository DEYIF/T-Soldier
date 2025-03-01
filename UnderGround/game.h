#ifndef GAME_H
#define GAME_H
#include<hero.h>
#include<enemy.h>
#include<pause.h>
#include <QWidget>
#include<QTimer>
#include<vector>
#include<QKeyEvent>
#include<QPaintEvent>
#include<QPainter>
#include<login.h>
#include<QPixmap>
#include<QVector>
#include<dia.h>
#include<diaboard.h>
namespace Ui {
class Game;
}

class Game : public QWidget
{
    Q_OBJECT
private:
    //QSet<int> pressedKeys;
public:
    explicit Game(QWidget *parent = 0);
    ~Game();
    bool gameIsRunning;//判断游戏是否正在运行
    //地图贴图
    QPixmap mapPic[30];
    //0泥土 1草 2石块 3宝箱关闭 4宝箱打开 5Goblin1
    //6Bokoblin1 7迷雾2 8迷雾3 9迷雾4 10绿色迷雾
    //11装备栏未选中 12装备栏选中 13林克背景图
    //14Goblin2 15Goblin3   16Bokoblin2
    //17Hole    18Mop     19Board   20DoorClosed   21DoorOpened

    //武器模块
    QPixmap LinkSword;
    QPixmap LinkSpear;
    QPixmap LinkMop;
    QPixmap Mop;
    QPixmap MasterSword;
    QPixmap BlueSpear;
    bool isChangeToSpear;
    bool isChangeToSword;
    bool isChangeToMop;
    int Equiped;//0剑    1矛

    QPixmap RedHeart;//心心

    QVector< QVector<int> > mapOne;
    //角色
    Hero *Link=new Hero;
    //敌人
    Enemy* EGroup=new Enemy[6];
    //Enemy *Goblin= new Enemy;
    //计时器
    QTimer timer;//英雄计时器
    QTimer Etim;//敌人计时器
    //int clock;
    //移动判定
    bool up;
    bool down;
    bool right;
    bool left ;
    //转向判定
    bool Diup;
    bool Didown;
    bool Diright;
    bool Dileft ;
    //攻击判定
    bool attack;
    //治疗判定
    bool heal;

    //作弊码模块
    bool cheatCode;
    int key2count1;
    int key2count2;
    int key1count;

    bool enemyAllGo(Enemy* eg);//判断敌人是否死光

    QTimer remove();
    void keyPressEvent(QKeyEvent *event);//键盘按下事件
    void keyReleaseEvent(QKeyEvent *event);//键盘释放事件
    void paintEvent(QPaintEvent *event);//绘图事件
    bool thereHasChest();//判断面前有没有宝箱
    bool thereHasBoard();//判断面前有没有路牌
    bool thereHasMarineBoard();//判断面前有没有马琳路牌
    bool thereHasMarine();//判断面前有没有马琳
    void EnemyAttack();//敌人攻击
    void showDiaMop();//显示获得拖把
signals:
    //void pressESC();//按下ESC
public slots:
    void UpdateEnemys();//更新敌人信息
    void UpdateHeroPos();//更新英雄信息
private:
    Ui::Game *ui;
};

#endif // GAME_H
