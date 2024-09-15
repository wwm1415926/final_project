#include "role_G.h"

Role_G::Role_G(int j,int i = 11, bool enemy = 1, int health = 1050, int attack = 150,
               int attack_interval = 1200, int  spd = 1, int cost = 0, QString name = "G"):
MyRole( i, j, enemy, health, attack,attack_interval,cost,name)
{
    this->spd=spd;
    state = 1;
    posx = 1150;
    posy = 50 + j * 100;
};

void Role_G::UpdateState(Game &game)
{

    foreach (MyRole *object, game.OurRoles)
    {
        if (object->posi == this->posi)
            posx += spd;
        // 根据攻击类型（近战或远程）进行不同的处理
        // 例如，如果是远程攻击，创建并发射子弹
    }
    posx -= spd;
    posi = (posx-Left_Width) / 100;

    foreach (myBullet *bullet, bullets)
    {
        bullet->posx++;
    }
}

QList<MyRole *> Role_G::AttackObject(int i, int j, bool enemy = 0,Game game)
{
    // 确定攻击对象并返回一个角色列表
    QList<MyRole *> objects;
    // 根据游戏逻辑确定攻击对象并添加到列表中
    foreach (MyRole *object, game.OurRoles)
    {
        if (object->posi == this->posi)
        {
            objects.append(object);
        }
        // 根据攻击类型（近战或远程）进行不同的处理
        // 例如，如果是远程攻击，创建并发射子弹
    }
    return objects;
}
void Role_G::be_attacked_near(int attack_)
{
    this->health -= attack_;
}

void Role_G::be_attacked_far(myBullet *bullet)
{

}

/*void Role_G::Attack(QList<MyRole *> Objects) //如果G是远程
{
    this->state = 2;
    myBullet *bullet = new myBullet("G", this->posx, this->posy, this->attack);
    foreach (MyRole *object_, AttackObject)
    {
        object_.be_attacked_yuan(bullet);
    }
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [=]
            { this->state = 1 });
    timer->start(1000);
}
*/
void Role_G::Attack(QList<MyRole *> Objects)
{
    //攻击动画
    // 对范围内所有目标发起攻击
    this->state = 2;
    foreach (MyRole *object_, AttackObject)
    {
        object_.be_attacked_naer(this->attack);
        // 根据攻击类型（近战或远程）进行不同的处理
        // 例如，如果是远程攻击，创建并发射子弹
    }
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [=]
            { this->state = 1 });
    timer->start(1000);
}
