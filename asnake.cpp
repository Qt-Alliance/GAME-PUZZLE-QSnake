/*贪食蛇类的实现*/
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "asnake.h"

aSnake::aSnake(int  w, int  h)
{
    height = h;
    width = w;
    length = 0;
    AddNode(w/2, h/2);
    PutFood();
    die = false;
    aDir = rand()%4+1;  //初始方向随机
}

aSnake::~aSnake(void)
{
    SnakeNode.clear();
}

void aSnake::AddNode(const int & w, const int & h)
{
    aNode * newNode = new aNode;
    newNode->x = w;
    newNode->y = h;
    SnakeNode.push_back(*newNode);
    length++;
    delete newNode;
}


void aSnake::Judge(void)
{
    //判断是否撞墙
    if (SnakeNode[0].x == 0 || SnakeNode[0].x == width ||
        SnakeNode[0].y == 0 || SnakeNode[0].y == height)
    {
        die = true;
        return ;
    }
/*    //判断蛇是否跟自己相撞
    for (int i = 1; i < length; i++)
    {
        if (SnakeNode[0].x == SnakeNode[i].x &&
            SnakeNode[0].y == SnakeNode[i].y)
        {
            die = true;
            return;
        }
    }

    //若两种情况均未发生，说明还活着。  */

    die = false;
}

//返回蛇的生死状态
bool aSnake::IsDie(void)
{
    return die;
}

void aSnake::Move(void)
{

    //记录蛇尾的位置，用来在吃到食物的时侯增加长度
    int lastX = SnakeNode[length-1].x;
    int lastY = SnakeNode[length-1].y;
    //从尾部开始处理除蛇头以外的蛇身的移动
    for (int i = length - 1; i > 0; i--)
    {
        SnakeNode[i].x = SnakeNode[i-1].x;
        SnakeNode[i].y = SnakeNode[i-1].y;
    }
    //根据当前方向处理蛇头
    //调用getDir获取蛇头方向
    switch (director=getDir())
    {
    case 1: //向上
        SnakeNode[0].y--;
        break;
    case 2: //向右
        SnakeNode[0].x++;
        break;
    case 3: //向下
        SnakeNode[0].y++;
        break;
    case 4: //向左
        SnakeNode[0].x--;
        break;
    default:
        break;
    }
    //看移动后的蛇是否吃到食物了，如果吃到，增加蛇的长度
    if (SnakeNode[0].x == Food.x && SnakeNode[0].y == Food.y)
    {
        AddNode(lastX, lastY);
        PutFood();
    }
    Judge();  //每次移动后调用判断函数更新蛇的生死状态
}

void aSnake::PutFood(void)
{
    int x, y;
    bool empty = false;
    srand(time(NULL));
    do
    {
        empty = true;
        x = rand()%(width-2)+1;
        y = rand()%(height-2)+1;
        for (int i = 0; i < length; i++)
        {
            if (SnakeNode[i].x == x &&
                SnakeNode[i].y == y)
            {
                empty = false;
                break;
            }
        }
    }while (empty == false);
    Food.x = x;
    Food.y = y;
}

void aSnake::OutputSnake(vector<aNode> & node,
                 aNode & food)
{
    node.resize(SnakeNode.size());
    node = SnakeNode;
    food = Food;
}

void aSnake::Clear(void)
{
    SnakeNode.clear();
    length = 0;
    AddNode(25, 25);
    director = 1;
}

int aSnake::getDir()
{
    int x,y,x1,x2,y1,y2;
    int a,b,c,d;
    \
    //当前蛇头与食物的距离
    x=SnakeNode[0].x-Food.x;
    y=SnakeNode[0].y-Food.y;
    //蛇头四周，也可以说是蛇头下一个移动位置与食物的距离
    x1=(SnakeNode[0].x+1)-Food.x;
    x2=(SnakeNode[0].x-1)-Food.x;
    y1=(SnakeNode[0].y-1)-Food.y;
    y2=(SnakeNode[0].y+1)-Food.y;
    //算出到达食物所需的距离
    a=y1*y1+x*x;
    b=y*y+x1*x1;
    c=y2*y2+x*x;
    d=y*y+x2*x2;
    //取与到达食物所需的距离最小的朝向方向
    if(a<=b&&a<=c&&a<=d/*&&director!=3*/)
        return  aDir=1;
    else if(b<=a&&b<=c&&b<=d/*&&director!=4*/)
        return  aDir=2;
    else if(c<=a&&c<=b&&c<=d/*&&director!=1*/)
        return  aDir=3;
    else if(d<=a&&d<=b&&d<=c/*&&director!=2*/)
        return  aDir=4;

}



