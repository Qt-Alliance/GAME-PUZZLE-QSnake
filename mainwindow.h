#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include "snake.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();

public slots:
    void timeout(void);   //自定义的槽函数，处理定时器时间，用于游戏更新
    void showAbout(void); //自定义的槽函数，显示关于信息
    void showHelp(void);  //自定义的槽函数，显示帮助信息
    void startGame(void); //自定义的槽函数，开始游戏
    void pauseGame(void); //自定义的槽函数，暂停游戏
    void speedUp(void); //自定义的槽函数，游戏加速
    void speedDown(void); //自定义的槽函数，游戏减速

public:
    void keyPressEvent(QKeyEvent * event); //处理按键消息
    void paintEvent(QPaintEvent * event); //处理重绘消息

public:
    void dealMenu(void);   //处理菜单的函数
    void setcolor();    //设置颜色

public:
    Snake snake; //贪食蛇的类
    bool isDie;  //游戏是否结束
    bool bRun;  //游戏是否运行的变量
    QTimer * timer; //游戏定时器
    int times; //定时器的频率
    int MenuBarSize; //菜单栏所占的位置
    QColor color;   //颜色

};

#endif
