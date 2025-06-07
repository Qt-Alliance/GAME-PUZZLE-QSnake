#ifndef ASNAKE_H
#define ASNAKE_H

/*贪食蛇模型的类定义*/
#include <iostream>
#include <vector>
using namespace std;

//蛇的结点
struct aNode
{
    int x;
    int y;
};


class aSnake

{
public:
    vector<aNode> SnakeNode;  //蛇的数据结构
    aNode Food;               //蛇吃的食物的座标
    int director;            //蛇头的前进方向 1-4:从上开始顺时针
    int length;              //蛇的全长
    bool die;                //是否死了
    int height;              //游戏区域的高度（y值)
    int width;               //游戏区域的宽度(x值)

    int aDir;                //蛇头将要朝向方向

public:
    aSnake(int w = 50, int h = 50);
    ~aSnake(void);
    void Move(void);                             //蛇头向当前方向前进1
    bool IsDie(void);                           //判断蛇是否死了
    void OutputSnake(vector<aNode> & node,
             aNode & food);  //将当前的蛇的数据结构复制
                                    //到node及food中供其以各种形式输出
    void Clear();  //将数据结构清空
    void Judge(void);                //蛇每前进一步，对蛇的状态进行判断
    void AddNode(const int & w, const int & h); //将蛇的长度加1
    void PutFood(void);              //随机放置食物

    int getDir();  //获得蛇头将要朝向的方向
};

#endif
