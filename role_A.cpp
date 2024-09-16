#include "role_A.h"

Role_A::Role_A(int i,int j,bool enemy,int health,int attack_power,int attack_interval,int cost,QString name)
    :MyRole( i, j, enemy, health, attack_power,attack_interval,cost,name){
    this->Attack_area.append(gridvec(this->posi+1,this->posj));
    this->state=1;
    this->be_attacking=false;
    this->timer_attackcd.start(this->attack_interval);
    this->timer_skillcd.start(15000);
};

void Role_A::UpdateState(Game &game)
{

    if(this->state==1)
    {
        if(!this->timer_attackcd.isActive())
        {
            qDebug()<<"line 17";
            this->AttackObject(&game);
           if(!this->Attack_list.empty()) this->state=2;
           qDebug()<<"line 20";
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

void Role_A::SkillBegin(Game &game){
    //this->Attack_area.append(gridvec(this->posi,this->posj+1));
    this->skill_open=true;
    this->timer_skilling.start(8000);
    this->timer_skilling.isSingleShot();
    game.money+=10;
    if(!this->timer_skilling.isActive())
    {
        this->timer_skilling.stop();
        this->skill_open=false;
        this->timer_skillcd.start(15000);
        this->timer_attackcd.isSingleShot();
    }
}

void Role_A::SkillEnd(){
    if(!this->timer_skillcd.isActive())
    {
        this->timer_skillcd.stop();
    }
}

void Role_A::Attack(Game *game)
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



