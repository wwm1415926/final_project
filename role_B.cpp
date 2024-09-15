
#include "role_B.h"

role_B::role_B(int i,int j,bool enemy=false,int health=1800,int attack_power=900,int attack_interval=2900,int cost=30,QString name="B")
    :MyRole( i, j, enemy, health, attack_power, attack_interval,cost,name){
    for(int i=1;i<=3;i++)
        this->Attack_area().append(gridvec(this->posi+i,this->posj));
    };

void role_B::UpdateState(Game &game)
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

void role_B::SkillBegin(Game &game){
    for(int i=this->posi;i<=this->posi+4;i++)
        for(int j=this->posj-1;j<=this->posj+1;j++)
            this->Attack_area().append(gridvec(i,j));
    this->temp=this->attack_interval;
    this->attack_interval=1000;
    this->skill_open=true;
    this->timer_skilling.start(15000);
    this->timer_skilling.isSingleShot();
    connect(this->timer_skilling,&QTimer::timeout,this,[=]{
        this->timer_skilling.stop();
        this->skill_open=false;
        this->timer_skillcd.start(20000);
        this->timer_attackcd.isSingleShot();
    });
}

void role_B::SkillEnd(){
    while(!this->Attack_area().empty())
        this->Attack_area().pop_back();
    for(int i=1;i<=3;i++)
        this->Attack_area().append(gridvec(this->posi+i,this->posj));
    this->attack_interval=this->temp;
    connect(this->timer_skillcd,&QTimer::timeout,this,[=]{
        this->timer_skillcd.stop();
    });
}


void role_B::Attack(Game *game){
    this->timer_attacking.start(500);
    this->timer_attacking.isSingleShot();
    for (auto object:Attack_list){
        myBullet*temp=new myBullet(this->name,this->posi,this->posj,this->attack_power);
        object->Bullets.append(temp);
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
