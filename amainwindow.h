#ifndef AMAINWINDOW_H
#define AMAINWINDOW_H

#include <QtGui>
#include "asnake.h"


class aMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    aMainWindow(QWidget * parent = 0);
    ~aMainWindow();

public slots:
    void timeout(void);   //自定义的槽函数，处理定时器时间，用于游戏更新
    void startGame(void); //自定义的槽函数，开始游戏
    void pauseGame(void); //自定义的槽函数，暂停游戏
    void speedUp(void); //自定义的槽函数，游戏加速
    void speedDown(void); //自定义的槽函数，游戏减速

public:

    void paintEvent(QPaintEvent * event); //处理重绘消息

public:
    void dealButton(void);   //处理按钮的函数
    void setcolor(void);    //设置颜色

public:
    aSnake snake; //贪食蛇的类
    bool isDie;  //游戏是否结束
    bool bRun;  //游戏是否运行的变量
    QTimer * timer; //游戏定时器
    int times; //定时器的频率
    int MenuBarSize; //菜单栏所占的位置
    QColor color;   //颜色

};

#endif
