#include "role_A.h"

Role_A::Role_A(int i,int j,bool enemy=false,int health=1500,int attack=500,int attack_interval=1000,int cost=8,QString name="A")
    :MyRole( i, j, enemy, health, attack,attack_interval,cost,name){};

void Role_A::UpdateState(Game &game)
{
    connect(timer_attack_interval,&QTimer::timeout,this,[=]{
        timer_attack_interval->stop();
    });
    if(this->state==1)
    {
        if(!timer_attack_interval->isActive()&&!timer_attacking->isActive())
        {
            this->AttackObject2(game);
            this->state=2;
            this->Attack(this->Attack_list,game);
        }
    }
}

void Role_A::AttackObject2(Game &game)
{
    MyRole *temp;
    temp->posi=100000;
    for(int i=0;i<game.EnemyRoles.size();i++)
    {
        if(game.EnemyRoles[i]->posj==this->posj&&game.EnemyRoles[i]->posi==this->posi+1)
        {
            if(game.EnemyRoles[i]->posi<temp->posi)
                temp=game.EnemyRoles[i];
        }
        this->Attack_list.append(temp);
    }
}

void Role_A::Attack(QList<MyRole*>Objects,Game &game)
{
    this->timer_attacking->start(500);
    connect(timer_attacking,&QTimer::timeout,this,[=]{
        timer_attacking->stop();
        this->state=1;
        timer_attack_interval->start(this->attack_interval);
    });
}




