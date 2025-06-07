#include "asnake.h"
#include "amainwindow.h"
#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

aMainWindow::aMainWindow(QWidget * parent)
{

    setWindowTitle(tr("demo"));
    MenuBarSize = 20;
    setFixedSize(710,510+MenuBarSize);
    dealButton();
    isDie = false;

    bRun = false;

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timeout()));
    times = 200;
    timer->start(times);
}


aMainWindow::~aMainWindow()
{
}


void aMainWindow::timeout(void)
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
        bRun = false;
        QMessageBox::information(this, tr("game over"),
                tr("you lose,game over!"));
        isDie = false;
        snake.Clear();
        return ;
    }
    update();
}


void aMainWindow::setcolor()
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


void aMainWindow::paintEvent(QPaintEvent * event)
{

    QPainter painter(this);
    painter.setBrush(Qt::gray);
    painter.drawRect(0, 0, 510, 530);

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

    vector<aNode> node;
    aNode food;
    snake.OutputSnake(node, food);

    setcolor();
    //画食物
    QColor red = QColor(color);
    painter.setBrush(red);
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
        painter.drawRect(10*node[i].x, 10*node[i].y+MenuBarSize, 10, 10);
    }
    node.clear();
    QWidget::paintEvent(event);

}


//处理按钮的函数
void aMainWindow::dealButton()
{
    QMenuBar * menuBar = new QMenuBar(this);
    QMenu * gameMenu = new QMenu(tr("This is a demo!"), menuBar);
    menuBar->addMenu(gameMenu);
    setMenuBar(menuBar);

    QPushButton * start = new QPushButton("start",this); //开始游戏按钮
    QPushButton * pause = new QPushButton("pause",this); //暂停游戏按钮
    QPushButton * speedDown = new QPushButton("speedDown",this); //减速按钮
    QPushButton * speedUp = new QPushButton("speedUp",this); //加速按钮
    start->setGeometry(550,70,120,60);
    pause->setGeometry(550,170,120,60);
    speedDown->setGeometry(550,270,120,60);
    speedUp->setGeometry(550,370,120,60);
    connect(start,SIGNAL(clicked()),this,SLOT(startGame()));
    connect(pause,SIGNAL(clicked()),this,SLOT(pauseGame()));
    connect(speedDown,SIGNAL(clicked()),this,SLOT(speedDown()));
    connect(speedUp,SIGNAL(clicked()),this,SLOT(speedUp()));

}


void aMainWindow::startGame(void)
{
    bRun = true;
    timer->start(times);
}

void aMainWindow::pauseGame(void)
{
    bRun = false;
    timer->stop();
}

void aMainWindow::speedUp(void)
{
    times -= 35;
    if (times <= 35)
    {
        times = 35;
    }
    timer->stop();
    timer->start(times);
}

void aMainWindow::speedDown(void)
{
    times += 35;
    if (times >= 500)
    {
        times = 500;
    }
    timer->stop();
    timer->start(times);
}


