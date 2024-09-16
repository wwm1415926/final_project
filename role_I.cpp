#include "role_I.h"

Role_I::Role_I(int j, int i, bool enemy, int health, int attack, int attack_interval, int cost, QString name)
    : MyRole(i, j, enemy, health, attack, attack_interval, cost, name){
    this->posx=Left_Width+posi*Cell_Size;
    this->posy=Up_Height+posj*Cell_Size;
    this->state=1;
    this->be_attacking=false;};

void Role_I::UpdateState(Game &game)
{

    if (this->state == 1)
    {
        if (!timer_attack_interval->isActive())
        {
            this->AttackObject(&game);
            this->state = 2;
        }
        this->be_attacked();
    }
    if (this->state == 2)
    {
        this->Attack(&game);
    }

    posx -= speed;
    posi = (posx - Left_Width) / 100;

    this->Attack_area.clear();
    this->Attack_area.append(gridvec(this->posi, this->posj));
    this->Attack_area.append(gridvec(this->posi - 1, this->posj));
    if (this->posj >= 1)
    {
        this->Attack_area.append(gridvec(this->posi, this->posj - 1));
        this->Attack_area.append(gridvec(this->posi - 1, this->posj - 1));
    }
    if (this->posj <= 4)
    {
        this->Attack_area.append(gridvec(this->posi, this->posj + 1));
        this->Attack_area.append(gridvec(this->posi - 1, this->posj + 1));
    }
    foreach (MyRole *object, game.OurRoles)
    {
        if (object->posi == this->posi)
        {
            posx += speed;
            this->Attack_area.clear();
            this->Attack_area.append(gridvec(this->posi, this->posj));
            this->Attack_area.append(gridvec(this->posi - 1, this->posj));
        }

        // 根据攻击类型（近战或远程）进行不同的处理
        // 例如，如果是远程攻击，创建并发射子弹
    }
}

void Role_I::SkillBegin(Game&game) {}

void Role_I::SkillEnd() {}

void Role_I::Attack(Game *game)
{
    this->timer_attacking->start(500);
    for (auto object : Attack_list)
    {
        myBullet *temp = new myBullet(this->name, this->posi, this->posj, this->attack_power);
        object->Bullets.append(temp);
    }
    connect(timer_attacking, &QTimer::timeout, this, [=]
            {
        timer_attacking->stop();
        this->state=1;
        timer_attack_interval->start(this->attack_interval);
        for (auto object:Attack_list){
            object->be_attacking=false;
            Attack_list.pop_back();
        } });
}
