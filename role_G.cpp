#include "role_G.h"

Role_G::Role_G(int j, int i, bool enemy, int health, int attack, int attack_interval, int cost, QString name)
    : MyRole(i, j, enemy, health, attack, attack_interval, cost, name){};

void Role_G::UpdateState(Game &game)
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
        this->Attack(this->Attack_list, &game);
    }

    posx -= speed;
    posi = (posx - leftwidth) / 100;
    this->Attack_area().clear();

    foreach (MyRole *object, game.OurRoles)
    {
        if (object->posi == this->posi)
        {
            posx += speed;
            this->Attack_area().append(gridvec(this->posi, this->posj));
            this->Attack_area().append(gridvec(this->posi - 1, this->posj));
        }

        // 根据攻击类型（近战或远程）进行不同的处理
        // 例如，如果是远程攻击，创建并发射子弹
    }
}

void Role_G::SkillBegin() {}
void Role_G::AttackObject(Game *game)
{
    MyRole *temp = new MyRole();
    temp->posi = 100;
    for (int i = 0; i < game->EnemyRoles.size(); i++)
    {
        for (auto area : this->Attack_area())
        {
            if (game->EnemyRoles[i]->posj == area.j && game->EnemyRoles[i]->posi == area.j)
            {
                if (game->EnemyRoles[i]->posi < temp->posi)
                    temp = game->EnemyRoles[i];
            }
            this->Attack_list.append(temp);
        }
    }
}
void Role_G::SkillEnd() {}
void Role_G::Attack(QList<MyRole *> Objects, Game *game)
{
    this->timer_attacking->start(500);
    for (auto object : Attack_list)
    {
        object->be_attacking = true;
        object->health -= this->attack_power;
    }

    connect(timer_attacking, &QTimer::timeout, this, [=]
    {
        timer_attacking->stop();
        this->state = 1;
        timer_attack_interval->start(this->attack_interval);
        for (auto object : Attack_list)
        {
            object->be_attacking = false;
            Attack_list.pop_back();
        }
    });
}
