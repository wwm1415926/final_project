#ifndef GRID_H
#define GRID_H
#endif // GRID_H

/*
 * 简化键盘按键和方向的表示
 */
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
#define QUEEN 5
#define ECHO 6
#define ZOO 7
#define CHAT 8
#define LEO 9
#define ROMIO 10
#define UFO 11
#define DOG 12

/*
 *与游戏界面相关的常量参数
 */
# define Play_Width 1200
# define Play_Height (720)
# define Prop_Widget_Width 1200
# define Prop_Widget_Height (100)
# define  Prop_Number 4
# define Cell_Size 50
# define Button_Size 70
# define Left_Width 30
# define Up_Height (100)

/*
 *定义游戏方格结构体及相应运算，简化后续表述
 */
typedef struct gridvec
{
    /*
     * j,i对应的是格子;x,y对应坐标
     * i->x轴（横向）宽度，j->y轴（纵向
     */
    int i;
    int j;
    gridvec(int i = 0, int j = 0) : i(i), j(j)
    {}
    /*
     *返回this相对于x所在的方位
     */
    int operator-(gridvec x)
    {
        if (i - x.i == 1 && j == x.j)
        {
            return RIGHT;
        }
        if (i - x.i == -1 && j == x.j)
        {
            return LEFT;
        }
        if (j - x.j == 1 && i== x.i)
        {
            return DOWN;
        }
        if (j - x.j == -1 && i == x.i)
        {
            return UP;
        }
        return 0;
    }
    /*
     * 返回this加改变的方向后对应的坐标
     */
    gridvec operator+(int side) const
    {

        switch (side)
        {
        case UP:
        case 5:
        case 7:
            return gridvec{i, j- 1};
            break;
        case DOWN:
        case 9:
        case 11:
            return gridvec{i, j + 1};
            break;
        case LEFT:
        case 8:
        case 12:
            return gridvec{i- 1, j};
            break;
        case RIGHT:
        case 6:
        case 10:
            return gridvec{i + 1, j};
            break;
        default:
            break;
        }
        return gridvec{j, i};
    }
    /*
     *判断坐标是否超出游戏地图范围
     */
    bool OutGameScene(){
        if(i < 0 || i*Cell_Size>= Play_Width || j < 0 ||j*Cell_Size >=(Play_Height-Prop_Widget_Height))return true;
        return false;
    }

}GridVec;



