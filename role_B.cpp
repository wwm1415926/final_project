
#include "role_B.h"

role_B::role_B(int i,int j,bool enemy,int health,int attack_power,int attack_interval,int cost,QString name)
    :MyRole( i, j, enemy, health, attack_power, attack_interval,cost,name){
    for(int i=0;i<=3;i++)
        this->Attack_area.append(gridvec(this->posi+i,this->posj));
    this->state=1;
    this->be_attacking=false;
    this->timer_attackcd.start(this->attack_interval);
    this->timer_attackcd.setSingleShot(true);
    this->timer_skillcd.start(20000);
    this->timer_skillcd.setSingleShot(true);
    this->is_attacking=false;
};

void role_B::UpdateState(Game &game)
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

void role_B::SkillBegin(Game &game){
    for(int i=this->posi;i<=this->posi+4;i++)
        for(int j=this->posj-1;j<=this->posj+1;j++)
            this->Attack_area.append(gridvec(i,j));
    this->temp=this->attack_interval;
    this->attack_interval=1000;
    this->skill_open=true;
    this->timer_skilling.start(15000);
    this->timer_skilling.setSingleShot(true);
}

void role_B::SkillEnd(){
    while(!this->Attack_area.empty())
        this->Attack_area.pop_back();
    for(int i=0;i<=3;i++)
        this->Attack_area.append(gridvec(this->posi+i,this->posj));
    this->attack_interval=this->temp;
    this->state=1;
    this->skill_open=false;
    this->timer_skillcd.start(20000);
    this->timer_attackcd.setSingleShot(true);
}


void role_B::Attack(Game *game){
    if(!is_attacking){
        is_attacking=true;
        this->timer_attacking.start(700);
        this->timer_attacking.setSingleShot(true);

        for (auto object:Attack_list){
            if(object==nullptr)continue;

            else{
                myBullet*temp=new myBullet(this->name,this->posi*Cell_Size+Left_Width+40,this->posj*Cell_Size+Up_Height,this->attack_power);
                if(temp!=NULL)object->Bullets.push_back(temp);
            }

        }
    }
    if(!this->timer_attacking.isActive())
    {
        qDebug()<<"111";

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

