
#include "role_F.h"

role_F::role_F(int i,int j,bool enemy=false,int health=1650,int attack_power=0,int attack_interval=0,int cost=13,QString name="F")
    :MyRole( i, j, enemy, health, attack_power, attack_interval,cost,name){
    for(int i=this->posi;i<=this->posi+5;i++)
        for(int j=this->posj-1;j<=this->posj+1;j++)
            this->Attack_area().append(gridvec(i,j));
};

void role_F::UpdateState(Game &game)
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

void role_F::SkillBegin(Game &game){

    this->skill_open=true;
    for(int i=0;i<game.OurRoles.size();i++)
    {
        if(game.OurRoles[i]->posi>=this->posi&&game.OurRoles[i]->posi<=this->posi+5&&game.OurRoles[i]->posj>=this->posj-1&&game.OurRoles[i]->posj<=this->posj+1)
            game.OurRoles[i]->health+=500;
    }
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

void role_F::SkillEnd(){
    if(!this->timer_skillcd.isActive())
    {
        this->timer_skillcd.stop();
    }
}

