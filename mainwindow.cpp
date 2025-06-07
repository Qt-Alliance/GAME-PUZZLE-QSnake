#include "snake.h"
#include "mainwindow.h"
#include <iostream>
#include <vector>
#include <QtGui>
#include <ctime>
using namespace std;

MainWindow::MainWindow()
{

    setWindowTitle(tr("snake"));
    MenuBarSize = 20;//菜单栏所占的位置
    setFixedSize(510,510+MenuBarSize);
    dealMenu();
    isDie = false;
    bRun = false; //开始的时侯不开始游戏
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timeout()));//timeout()时间溢出
    times = 200;
    timer->start(times);

}


MainWindow::~MainWindow()
{
}


void MainWindow::timeout(void)
{
    if (bRun == false)
    {
        timer->stop();
        return ;
    }

    snake.Move();
    isDie = snake.IsDie();


    if (isDie)
    {
        //停止计时器，输出游戏结束信息
        timer->stop();
        times = 200;
        bRun = false;
        QMessageBox::information(this, tr("game over"),
                tr("you lose,game over!"));
        isDie = false;
        snake.Clear();
        return ;
    }
    update();
}

void MainWindow::setcolor()
{
    srand(time(NULL));
    switch(rand()%6)
    {
    case 0:
        color = Qt::red;
        break;
    case 1:
        color = Qt::yellow;
        break;
    case 2:
        color = Qt::green;
        break;
    case 3:
        color = Qt::blue;
        break;
    case 4:
        color = Qt::cyan;
        break;
    case 5:
        color = Qt::magenta;
        break;
    }
}

void MainWindow::paintEvent(QPaintEvent * event)
{
    QPainter painter(this);
    painter.setBrush(Qt::gray);
    painter.drawRect(0, 0, 510, 520+MenuBarSize);

    //画墙
    painter.setBrush(Qt::white);
    painter.drawRect(0, 0+MenuBarSize, 510, 10);  //上
    painter.drawRect(0, 500+MenuBarSize, 510, 10); //下
    painter.drawRect(0, 0+MenuBarSize, 10, 510); //左
    painter.drawRect(500, 0+MenuBarSize, 10, 510); //右



    if (isDie || !bRun)
    {
        return ;
    }


    vector<Node> node;
    Node food;
    snake.OutputSnake(node, food);

    setcolor();
    //画食物
    painter.setBrush(color);
    painter.drawEllipse(10*food.x, 10*food.y+MenuBarSize, 10, 10);


    //画蛇，蛇头跟蛇身用不同的颜色
    //蛇头
    painter.setBrush(Qt::yellow);
    painter.drawRect(10*node[0].x, 10*node[0].y+MenuBarSize, 10, 10);
    //蛇身
    painter.setBrush(color);
    int n = node.size();
    for (int i = 1; i < n; i++)
    {
        painter.drawRect(10*node[i].x, 10*node[i].y+MenuBarSize ,10, 10);
    }
    node.clear();

}


void MainWindow::keyPressEvent(QKeyEvent * event)
{
    int direct = 0;
    switch (event->key())
    {
    case Qt::Key_Up:
        direct = 1;
        break;
    case Qt::Key_Right:
        direct = 2;
        break;
    case Qt::Key_Down:
        direct = 3;
        break;
    case Qt::Key_Left:
        direct = 4;
        break;
    case Qt::Key_U:
        speedUp();
        break;
    case Qt::Key_D:
        speedDown();
        break;
    default:
        break;
    }
    snake.ChangeDirector(direct);

}

//处理菜单的函数
void MainWindow::dealMenu(void)
{
    QMenuBar * menuBar = new QMenuBar(this);
    QMenu * gameMenu = new QMenu(tr("game"), menuBar);
    QMenu * helpMenu = new QMenu(tr("help"), menuBar);
    //添加游戏菜单项
    QAction * start = new QAction(tr("start"), gameMenu);
    QAction * pauseGame = new QAction(tr("pause"), gameMenu);
    QAction * speedUp = new QAction(tr("up speed"), gameMenu);
    QAction * speedDown = new QAction(tr("down speed"), gameMenu);
    QAction * quitGame = new QAction(tr("quit"), gameMenu);
    gameMenu->addAction(start);
    gameMenu->addAction(pauseGame);
    gameMenu->addAction(speedUp);
    gameMenu->addAction(speedDown);
    gameMenu->addAction(quitGame);
    menuBar->addMenu(gameMenu);
    connect(start, SIGNAL(triggered()), this, SLOT(startGame()));
    connect(pauseGame, SIGNAL(triggered()), this, SLOT(pauseGame()));
    connect(speedUp, SIGNAL(triggered()), this, SLOT(speedUp()));
    connect(speedDown, SIGNAL(triggered()), this, SLOT(speedDown()));
    connect(quitGame, SIGNAL(triggered()), this, SLOT(close()));
    //添加帮助和关于菜单项
    QAction * helpGame = new QAction(tr("help"), helpMenu);
    QAction * aboutGame = new QAction(tr("about"), helpMenu);
    helpMenu->addAction(helpGame);
    helpMenu->addAction(aboutGame);
    menuBar->addMenu(helpMenu);
    connect(helpGame, SIGNAL(triggered()), this, SLOT(showHelp()));
    connect(aboutGame, SIGNAL(triggered()), this, SLOT(showAbout()));
    //将菜单加入菜单栏
    menuBar->addMenu(helpMenu);

    //设置菜单栏
    setMenuBar(menuBar);


}


void MainWindow::showAbout(void)
{
    QMessageBox::information(this, tr("about"),
                   tr("by amoya"));
}

void MainWindow::showHelp(void)
{
    QMessageBox::information(this, tr("help"),
                   tr("everyone knows it"));
}

void MainWindow::startGame(void)
{
    bRun = true;
    timer->start(times);
}

void MainWindow::pauseGame(void)
{
    bRun = false;
    timer->stop();
}

void MainWindow::speedUp(void)
{
    times -= 35;
    if (times <= 35)
    {
        times = 35;
    }
    timer->stop();
    timer->start(times);
}

void MainWindow::speedDown(void)
{
    times += 35;
    if (times >= 500)
    {
        times = 500;
    }
    timer->stop();
    timer->start(times);
}
