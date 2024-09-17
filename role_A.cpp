#include "role_A.h"

Role_A::Role_A(int i,int j,bool enemy,int health,int attack_power,int attack_interval,int cost,QString name)
    :MyRole( i, j, enemy, health, attack_power,attack_interval,cost,name){
    this->Attack_area.append(gridvec(this->posi+1,this->posj));
    this->Attack_area.append(gridvec(this->posi,this->posj));
    this->state=1;
    this->be_attacking=false;
    this->timer_attackcd.start(this->attack_interval);
    this->timer_attackcd.setSingleShot(true);
    this->timer_skillcd.start(15000);
    this->timer_skillcd.setSingleShot(true);
    this->is_attacking=false;
};

void Role_A::UpdateState(Game &game)
{

    if(this->state==1)
    {
        if(!this->timer_attackcd.isActive())
        {
            this->AttackObject(&game);
            if(!this->Attack_list.empty())
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
            qDebug()<<"line 34";
            if(this->skill_open==false)SkillBegin(game);
            this->AttackObject(&game);
            if(!this->Attack_list.empty())this->state=2;
        }
        if(!this->timer_skilling.isActive())SkillEnd();
        this->be_attacked();
    }
}

void Role_A::SkillBegin(Game &game){
    this->skill_open=true;
    this->timer_skilling.start(2000);
    this->timer_skilling.setSingleShot(true);
    game.money+=10;
}

void Role_A::SkillEnd(){
    this->state=1;
    this->skill_open=false;
    this->timer_skillcd.start(15000);
    this->timer_attackcd.setSingleShot(true);
}

void Role_A::Attack(Game *game)
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
        Attack_list.clear();
    }
}





