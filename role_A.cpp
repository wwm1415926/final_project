#include "role_A.h"

Role_A::Role_A(int i,int j,bool enemy=false,int health=1500,int attack=500,int attack_interval=1000,int cost=8,QString name="A")
    :MyRole( i, j, enemy, health, attack,attack_interval,cost,name){};

void Role_A::UpdateState(Game &game)
{

    if(this->state==1)
    {
        if(!timer_attack_interval->isActive())
        {
            this->AttackObject(&game);
            this->state=2;
        }
        this->be_attacked();
    }
    if(this->state==2){
        this->Attack(this->Attack_list,&game);
    }
    if(this->state==3){
        if(!this->timer_skilling.isActive()){
            this->state=1;
            SkillEnd();
        }
        if(!timer_attack_interval->isActive())
        {
            SkillBegin();
            this->AttackObject(&game);
            this->state=2;
        }
        this->be_attacked();
    }
}

void Role_A::SkillBegin(){
    this->Attack_area().append(gridvec(this->posi,this->posj+1));
}
void  Role_A::AttackObject(Game *game)
{
    MyRole *temp;
    temp->posi=100000;
    for(int i=0;i<game->EnemyRoles.size();i++)
    {
        for(auto area:this->Attack_area()){
            if(game->EnemyRoles[i]->posj==area.j&&game->EnemyRoles[i]->posi==area.j)
        {
            if(game->EnemyRoles[i]->posi<temp->posi)
                temp=game->EnemyRoles[i];
        }
        this->Attack_list.append(temp);
    }
}
}
void Role_A::SkillEnd(){
    while(!this->Attack_area().empty())
}
void Role_A::Attack(QList<MyRole*>Objects,Game *game)
{
    this->timer_attacking->start(500);
    for (auto object:Attack_list){
        object->be_attacking=true;
        object->health-=this->attack_power;
    }
    connect(timer_attacking,&QTimer::timeout,this,[=]{
        timer_attacking->stop();
        if(this->timer_skilling.isActive())this->state=3;
        this->state=1;
        timer_attack_interval->start(this->attack_interval);
        for (auto object:Attack_list){
            object->be_attacking=false;
            Attack_list.pop_back();
        }
    });
}





