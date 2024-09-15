#include "role_D.h"


role_D::role_D(int i,int j,bool enemy=false,int health=1700,int attack_power=1000,int attack_interval=2400,int cost=24,QString name="D")
    :MyRole( i, j, enemy, health,attack_power, attack_interval,cost,name){
    for(int i=1;i<=3;i++)
        this->Attack_area().append(gridvec(this->posi+i,this->posj));
    };

void role_D::UpdateState(Game &game)
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

void role_D::SkillBegin(Game &game){
    this->temp=this->attack_power;
    this->attack_power=1400;
    this->skill_open=true;
    this->timer_skilling.start(10000);
    this->timer_skilling.isSingleShot();
    connect(this->timer_skilling,&QTimer::timeout,this,[=]{
        this->timer_skilling.stop();
        this->skill_open=false;
        this->timer_skillcd.start(20000);
        this->timer_attackcd.isSingleShot();
    });
}

void role_D::Attack(Game *game){
    this->timer_attacking.start(500);
    this->timer_attacking.isSingleShot();
    for (auto object:Attack_list){
        myBullet*temp=new myBullet(this->name,this->posi,this->posj,this->attack_power);
        myBullet*xuanyun=new myBullet(this->name,this->posi,this->posj,0);
        object->Bullets.append(temp);
        object->Bullets.append(xuanyun);
    }
    connect(this->timer_attacking,&QTimer::timeout,this,[=]{
        timer_attacking.stop();
        if(this->timer_skilling.isActive())this->state=3;
        this->state=1;
        this->timer_attackcd.start(this->attack_interval);
        this->timer_attackcd.isSingleShot();
        for (auto object:Attack_list){
            object->be_attacking=false;
            Attack_list.pop_back();
        }
    });
}
