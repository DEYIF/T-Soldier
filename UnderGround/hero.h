#ifndef HERO_H
#define HERO_H

#include <QWidget>
#include<qpixmap.h>
#include<enemy.h>
#include<QVector>
class Hero :public QWidget
{
    Q_OBJECT
public:
    int Hp;//Hero生命值
    int maxHp;//Hero最大生命值
    int En;//Hero精力

    //Hero坐标
    int x;
    int y;

    //Hero长宽
    int wid;
    int hei;

    //Hero朝向
    int direction;//0下 1上 2左 3右

    //Hero武器
    int weapon;//0剑 1矛 2拖把
    bool hadSpear;
    bool hadMop;

    QPixmap ChaoXiang[4];//Hero不同朝向的图片
    QPixmap walk;//Hero走路的图片
    //地图 要与game里的地图同步
    QVector< QVector<int> >mapOne;
public:
    explicit Hero(QWidget *parent = 0);
    bool heroIsIn(int left,int right,int up,int down);//判断Hero是否在指定区域内 左右上下
    bool heroIsInPoint(int xx,int yy);//判定hero是否在某个坐标
    bool heroIsInMap(QVector< QVector<int> > map);//hero在非石头的地图内
    int getX();
    int getY();
    int getWid();
    int getHei();
    int getHp();
    int getEn();
    QPixmap getpic(int);

signals:
public slots:
    void heroTrun(bool up,bool down,bool left,bool right);//Hero转向
    void heroMove(bool up,bool down,bool left,bool right);//Hero坐标移动
    void heroAttack(bool,int, Enemy *);//Hero攻击
    void heroHeal(bool,Enemy*);//Hero治疗
    void heroReduceHp(int damage);//Hero扣血
};

#endif // HERO_H
