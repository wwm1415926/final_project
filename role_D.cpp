#include "role_D.h"


role_D::role_D(int i,int j,bool enemy,int health,int attack_power,int attack_interval,int cost,QString name)
    :MyRole( i, j, enemy, health,attack_power, attack_interval,cost,name){
    this->state=1;
    this->be_attacking=false;
    for(int i=0;i<=3;i++)
        this->Attack_area.append(gridvec(this->posi+i,this->posj));
    this->timer_attackcd.start(this->attack_interval);
    this->timer_attackcd.setSingleShot(true);
    this->timer_skillcd.start(20000);
   this->timer_skillcd.setSingleShot(true);
    this->is_attacking=false;
};

void role_D::UpdateState(Game &game)
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

void role_D::SkillBegin(Game &game){
    this->temp=this->attack_power;
    this->attack_power=1400;
    this->skill_open=true;
    this->timer_skilling.start(10000);
    this->timer_skilling.setSingleShot(true);
}

void role_D::SkillEnd(){
    this->attack_power=this->temp;
    this->state=1;
    this->skill_open=false;
    this->timer_skillcd.start(20000);
    this->timer_attackcd.setSingleShot(true);
}

void role_D::Attack(Game *game){
    if(!is_attacking){
        is_attacking=true;
        this->timer_attacking.start(700);
        this->timer_attacking.setSingleShot(true);
        for (auto object:Attack_list){
            if(object==nullptr)continue;
            myBullet*temp=new myBullet(this->name,this->posi*Cell_Size+Left_Width+40,this->posj*Cell_Size+Up_Height,this->attack_power);
            if(!this->timer_skilling.isActive())
            {
                myBullet*xuanyun=new myBullet(this->name,this->posi*Cell_Size+Left_Width+40,this->posj*Cell_Size+Up_Height,0);
                object->Bullets.append(xuanyun);
            }
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
