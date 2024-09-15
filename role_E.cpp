#include "role_E.h"


role_E::role_E(int i,int j,bool enemy,int health,int attack_power,int attack_interval,int cost,QString name)
    :MyRole( i, j, enemy, health,attack_power, attack_interval,cost,name){
    this->Attack_area.append(gridvec(this->posi+1,this->posj));
};

void role_E::UpdateState(Game &game)
{

    if(this->state==1)
    {
        if(!this->timer_attackcd.isActive())
        {
            this->AttackObject(&game);
            this->state=2;
        }
        this->be_attacked();
    }
    if(this->state==2){
        this->Attack(&game);
    }
    if(this->state==3){
        if(!this->timer_skillcd.isActive())
        {
            if(this->skill_open==false)
                SkillBegin(game);
            this->AttackObject(&game);
            this->state=2;
        }
        if(!this->timer_skilling.isActive()){
            this->state=1;
            SkillEnd();
        }
        this->be_attacked();
    }
}

void role_E::SkillBegin(Game &game){
    this->skill_open=true;
    this->temp=this->health;
    this->health=4000;
    this->timer_skilling.start(15000);
    this->timer_skilling.isSingleShot();
    if(!this->timer_skilling.isActive())
    {
        this->timer_skilling.stop();
        this->skill_open=false;
        this->timer_skillcd.start(20000);
        this->timer_attackcd.isSingleShot();
    }
}

void role_E::SkillEnd(){
    this->health=3500*(this->health/4000);
    this->health+=350;
    if(!this->timer_attackcd.isActive())
    {
        this->timer_skillcd.stop();
    }
}

void role_E::Attack(Game *game)
{
    this->timer_attacking.start(500);
    this->timer_attacking.isSingleShot();
    for (auto object:Attack_list){
        object->be_attacking=true;
        object->health-=this->attack_power;
    }
    if(!this->timer_attackcd.isActive())
    {
        this->timer_attacking.stop();
        if(this->timer_skilling.isActive())this->state=3;
        this->state=1;
        this->timer_attacking.start(this->attack_interval);
        this->timer_attacking.isSingleShot();
        for (auto object:Attack_list){
            object->be_attacking=false;
            Attack_list.pop_back();
        }
    }
}
