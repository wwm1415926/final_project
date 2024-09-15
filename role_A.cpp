#include "role_A.h"

Role_A::Role_A(int i,int j,bool enemy=false,int health=1500,int attack=500,int attack_interval=1000,int cost=8,QString name="A")
    :MyRole( i, j, enemy, health, attack,attack_interval,cost,name){};

void Role_A::UpdateState(Game &game)
{
    for(int i=0;i<game.EnemyRoles.size();i++)
    {
        if(game.EnemyRoles[i]->posi==this->posi+1&&game.EnemyRoles[i]->posj==this->posj)
        {
            timer1=new QTimer(this);
            timer2=new QTimer(this);
            if(this->attack_cd==false)
            {
                this->state=2;
                timer1->start(500);
                connect(timer1,&QTimer::timeout,this,[=]{
                    this->state=1;
                    this->attack_cd=true;
                    timer1->stop();
                });
            }
            else
            {
                timer2->start(this->attack_interval);
                connect(timer2,&QTimer::timeout,this,[=]{
                    this->attack_cd=false;
                    timer2->stop();
                });
            }
        }
    }
}





