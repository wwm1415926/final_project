#include "role_E.h"


role_E::role_E(int i,int j,bool enemy,int health,int attack_power,int attack_interval,int cost,QString name)
    :MyRole( i, j, enemy, health,attack_power, attack_interval,cost,name){
    this->Attack_area.append(gridvec(this->posi+1,this->posj));
     this->Attack_area.append(gridvec(this->posi,this->posj));
    this->state=1;
    this->be_attacking=false;
    this->timer_attackcd.start(this->attack_interval);
    this->timer_attackcd.setSingleShot(true);
    this->timer_skillcd.start(20000);
    this->timer_skillcd.setSingleShot(true);
    this->is_attacking=false;
};

void role_E::UpdateState(Game &game)
{
    this->be_attacked();
    if(this->state==1)
    {
        if(!this->timer_attackcd.isActive())
        {
            this->AttackObject(&game);
            if(!this->Attack_list.empty())
                this->state=2;
        }

    }
    if(this->state==2){
        this->Attack(&game);
    }
    if(this->state==3){
        if(!this->timer_skillcd.isActive())
        {
            qDebug()<<"line 34";
            if(this->skill_open==false)SkillBegin(game);
            this->AttackObject(&game);
            if(!this->Attack_list.empty())this->state=2;
        }
        if(!this->timer_skilling.isActive())SkillEnd();
    }
}

void role_E::SkillBegin(Game &game){
    this->skill_open=true;
    this->temp=this->health;
    this->health=4000;
    this->timer_skilling.start(15000);
    this->timer_skilling.setSingleShot(true);
}

void role_E::SkillEnd(){
    this->health=3500*(this->health/4000);
    this->health+=350;
    this->state=1;
    this->skill_open=false;
    this->timer_skillcd.start(20000);
    this->timer_attackcd.setSingleShot(true);
}

void role_E::Attack(Game *game)
{
    if(!this->is_attacking)
    {
        this->is_attacking=true;
        this->timer_attacking.start(700);
        this->timer_attacking.setSingleShot(true);
        for (auto object:Attack_list){
            if(object==nullptr)continue;
            object->be_attacking=true;
            object->health-=this->attack_power;
        }
    }
    if(!this->timer_attacking.isActive())
    {
        if(this->timer_skilling.isActive())
            this->state=3;
        else
            this->state=1;
        this->is_attacking=false;
        this->timer_attacking.start(this->attack_interval);
        this->timer_attacking.setSingleShot(true);
        for (auto object:Attack_list){
            object->be_attacking=false;
            Attack_list.pop_back();
        }
    }
}

