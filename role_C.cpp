#include "role_C.h"


role_C::role_C(int i,int j,bool enemy,int health,int attack_power,int attack_interval,int cost,QString name)
    :MyRole( i, j, enemy, health, attack_power,attack_interval,cost,name){
    for(int i=0;i<=4;i++)
        this->Attack_area.append(gridvec(this->posi+i,this->posj));
    this->state=1;
    this->be_attacking=false;
    this->timer_attackcd.start(this->attack_interval);
    this->timer_attackcd.setSingleShot(true);
    this->timer_skillcd.start(20000);
    this->timer_skillcd.setSingleShot(true);
    this->is_attacking=false;
};

void role_C::UpdateState(Game &game)
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

void role_C::SkillBegin(Game &game){
    this->attack_interval=1600;
    this->attack_power*=2;
    this->skill_open=true;
}

void role_C::SkillEnd(){};

void role_C::Attack(Game *game){
    if(!is_attacking){
        is_attacking=true;
        this->timer_attacking.start(700);
        this->timer_attacking.setSingleShot(true);
        for (auto object:Attack_list){
            if(object==nullptr)continue;
            myBullet*temp=new myBullet(this->name,this->posi*Cell_Size+Left_Width+40,this->posj*Cell_Size+Up_Height,this->attack_power);
            if(temp!=NULL)object->Bullets.push_back(temp);
        }
    }
    if(!this->timer_attacking.isActive())
    {
        if(this->timer_skilling.isActive())this->state=3;
        else
            this->state=1;
        this->is_attacking=false;
        this->timer_attackcd.start(this->attack_interval);
        this->timer_attackcd.setSingleShot(true);
        for (auto object:Attack_list){
            if(object!=NULL)object->be_attacking=false;
            Attack_list.pop_back();
        }
    }
}



