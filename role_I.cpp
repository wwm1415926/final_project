#include "role_I.h"

Role_I::Role_I(int j, int i, bool enemy, int health, int attack_power, int attack_interval, int cost, QString name)
    : MyRole(i, j, enemy, health, attack_power, attack_interval, cost, name){
    this->Attack_area.append(gridvec(this->posi, this->posj));
    if (this->posj >= 1)
    {
        this->Attack_area.append(gridvec(this->posi, this->posj - 1));
        this->Attack_area.append(gridvec(this->posi - 1, this->posj - 1));
    }
    if (this->posj <= 4)
    {
        this->Attack_area.append(gridvec(this->posi, this->posj + 1));
        this->Attack_area.append(gridvec(this->posi - 1, this->posj + 1));
    }
    this->Attack_area.append(gridvec(this->posi,this->posj));
    this->Attack_area.append(gridvec(this->posi-1,this->posj));
    this->state=1;
    this->be_attacking=false;
    this->is_attacking=false;
    this->posx=this->posi*Cell_Size+Left_Width;
    this->posy=this->posj*Cell_Size+Up_Height;
    this->timer_attackcd.start(this->attack_interval);
    this->timer_attackcd.setSingleShot(true);
    this->spd=1;
};

void Role_I::UpdateState(Game &game)
{
    if (this->state == 1)
    {

        if (!timer_attackcd.isActive())
        {
            this->AttackObject(&game);
            if(!this->Attack_list.empty())this->state = 2;
        }
        this->be_attacked();
    }
    if (this->state == 2)
    {
        this->Attack(&game);
    }

    if(game.IsValid(GridVec(posi,posj))){
        posx-=spd;
        posi=(posx-Left_Width)/Cell_Size;
        this->Attack_area.clear();
        if (this->posj >= 1)
        {
            this->Attack_area.append(gridvec(this->posi, this->posj - 1));
            this->Attack_area.append(gridvec(this->posi - 1, this->posj - 1));
        }
        if (this->posj <= 4)
        {
            this->Attack_area.append(gridvec(this->posi, this->posj + 1));
            this->Attack_area.append(gridvec(this->posi - 1, this->posj + 1));
        }
    }
}
void Role_I::SkillBegin(Game&game) {}

void Role_I::SkillEnd() {}
void Role_I::Attack(Game *game){
    if(!is_attacking){
        is_attacking=true;
        this->timer_attacking.start(700);
        this->timer_attacking.setSingleShot(true);
        for (auto object:Attack_list){
            if(object==nullptr)continue;
            myBullet*temp=new myBullet(this->name,this->posi*Cell_Size+Left_Width+40,object->posj,this->attack_power);
            if(temp!=NULL)object->Bullets.push_back(temp);
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
         Attack_list.clear();
    }
}
