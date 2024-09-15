#include "role_C.h"


role_C::role_C(int i,int j,bool enemy=false,int health=1550,int attack_power=550,int attack_interval=1200,int cost=12,QString name="C")
    :MyRole( i, j, enemy, health, attack_power,attack_interval,cost,name){
    for(int i=1;i<=4;i++)
        this->Attack_area().append(gridvec(this->posi+i,this->posj));
    };

void role_C::UpdateState(Game &game)
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

void role_C::SkillBegin(Game &game){
    this->attack_interval=1600;
    this->attack_power*=2;
    this->skill_open=true;
}

void role_C::Attack(Game *game){
    this->timer_attacking.start(500);
    this->timer_attacking.isSingleShot();
    for (auto object:Attack_list){
        myBullet*temp=new myBullet(this->name,this->posi,this->posj,this->attack_power);
        object->Bullets.append(temp);
    }
    if(!this->timer_attackcd.isActive())
    {
        timer_attacking.stop();
        if(this->timer_skilling.isActive())this->state=3;
        this->state=1;
        this->timer_attackcd.start(this->attack_interval);
        this->timer_attackcd.isSingleShot();
        for (auto object:Attack_list){
            object->be_attacking=false;
            Attack_list.pop_back();
        }
    }
}
