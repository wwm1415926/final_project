#ifndef GAME_H
#define GAME_H
#include<QString.h>
#include<QList>
#include<grid.h>
#include<QPushButton>
#include<QTimer>
#include<mybullet.h>

class Item;
class Game;

/*
 *该类实现的所有除了矿物外所有建筑物
 */
class MyRole : public QPushButton
{

public:
    /*
     *角色性质参数
     */
    int posi,posj;//坐标
    bool enemy;//敌我角色
    int health,cost;
    double spd;
    QString name;//名称
    int state;//工作状态,1表示初始，2表示攻击态，3表示技能态,
    QTimer timer_attackcd,timer_attacking,timer_skillcd,timer_skilling;
    QList<myBullet*>bullets;

        /*
         * 攻击相关
         */
        int attack_interval;

    MyRole();
    /*
     *构造函数
     */
    MyRole(int i, int j, bool enemy, int health, int attack, int attack_interval, double spd, int cost, QString name);

    /*
     *判断角色是否相同
     */
    bool operator==(const MyRole *x) const;
    /*
     *是否可以放置
     */
    bool CanPlace(GridVec click, Game &game);

    /*
     *游戏人物更新函数，调用者是游戏界面，用以时刻更新人物状态
     */
    virtual void UpdateState(Game &game) = 0;

    /*
     *根据坐标和敌我，确定范围内的攻击对象
     */
    virtual QList<MyRole *> AttackObject(int i, int j, bool enemy) = 0;

    /*
     * 对范围内所有目标发起攻击;如果是近战就改变显示形态并让目标内的敌人频闪一下
     * 如果是远程，就要创立bullet对象？
     */
    virtual void Attack(QList<MyRole *> Objects) = 0;
    virtual void be_attacked(Game &game, int attack) = 0;
};

/*
 *Game对象，储存管理游戏数据和角色
 */
class Game
{
public:
    Game();
    /*
     *存储储存界面中所有的角色，方便快速遍历所有建筑
     */
    QList<MyRole *> OurRoles;
    QList<MyRole *> EnemyRoles;

    /*
     *，记录第几波等游玩参数
     */

    QTimer enemy_timer;
    int batch;//当前剩余批次数
    int round;//当前关次
    int money;//当前部署点
    int game_spd;//游戏速度
    /*
     *int spd1;
     *int spd2;
     *int spd3;//保留接口，后续可能接入商店加成
     */

    /*
     *初始化每一关的参数设置
     */
    void FirstGame();
    void SecondGame();
    /*
     *判断游戏地图上该位置是否闲置
     */
    bool IsValid(GridVec pos);
    /*
     *获取游戏地图上的建筑物
     */
    MyRole *GetRole(GridVec pos);
    /*
     *接收鼠标右键信号，移除我方角色
     */
    void RemoveRole(GridVec pos);
    static QVector<QVector<char>> EnemyList;



};

#endif // GAME_H
