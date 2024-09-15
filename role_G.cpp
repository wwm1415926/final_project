#include "role_G.h"

Role_G::Role_G(int i = 11, int j, bool enemy = 1, int health = 1050, int attack = 150, int attack_interval = 1200, double speed = 1, int cost = 0, QString name = "G")
{
    state = 1;
    posx = 1150;
    posy = 50 + j * 100;
};

void Role_G::UpdateState(Game &game)
{
    posx -= speed;
    foreach (MyRole *object, game.OurRoles)
    {
        if (object->i == this->i)
            posx += speed;
        // 根据攻击类型（近战或远程）进行不同的处理
        // 例如，如果是远程攻击，创建并发射子弹
    }

    i = (int)posx / 100;

    // 更新角色状态的代码
    // 例如，根据游戏逻辑更新角色的位置、生命值等
}

QList<MyRole *> Role_G::AttackObject(int i, int j, bool enemy = 0)
{
    // 确定攻击对象并返回一个角色列表
    QList<MyRole *> objects;
    // 根据游戏逻辑确定攻击对象并添加到列表中
    foreach (MyRole *object, game.OurRoles)
    {
        if (object->i == this->i)
        {
            objects.append(object);
        }
        // 根据攻击类型（近战或远程）进行不同的处理
        // 例如，如果是远程攻击，创建并发射子弹
    }
    return objects;
}
void Role_G::be_attacked(int attack_)
{
    this->health -= attack_;
    state = 4;
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [=]
            { state = 1 });
    timer->start(500);
}

void Role_G::Attack(QList<MyRole *> Objects)
{
    //攻击动画
    // 对范围内所有目标发起攻击
    state = 2;
    foreach (MyRole *object, AttackObject)
    {
        object_.be_attacked(this->attack);
        // 根据攻击类型（近战或远程）进行不同的处理
        // 例如，如果是远程攻击，创建并发射子弹
    }
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [=]
            { state = 1 });
    timer->start(1000);
}
