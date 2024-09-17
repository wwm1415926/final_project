#include "role_F.h"

role_F::role_F(int i,int j,bool enemy,int health,int attack_power,int attack_interval,int cost,QString name)
    :MyRole( i, j, enemy, health, attack_power, attack_interval,cost,name){
    this->state=1;
    this->be_attacking=false;
    for(int i=this->posi;i<=this->posi+5;i++)
        for(int j=this->posj;j<=this->posj+1;j++)
            this->Attack_area.append(gridvec(i,j));
    this->timer_attackcd.start(this->attack_interval);
    this->timer_attackcd.setSingleShot(true);
    this->timer_skillcd.start(20000);
    this->timer_skillcd.setSingleShot(true);
    this->is_attacking=false;
};

void role_F::UpdateState(Game &game)
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
            if(this->skill_open==false)SkillBegin(game);
            this->AttackObject(&game);
            if(!this->Attack_list.empty())this->state=2;
        }
        if(!this->timer_skilling.isActive())SkillEnd();
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
    this->timer_skilling.start(1000);
    this->timer_skilling.setSingleShot(true);
}

void role_F::SkillEnd()
{
    this->state=1;
    this->skill_open=false;
    this->timer_skillcd.start(20000);
    this->timer_attackcd.setSingleShot(true);
}

void role_F::Attack(Game *game)
{
    ;
}
