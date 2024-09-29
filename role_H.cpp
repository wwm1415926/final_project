#include "role_H.h"

Role_H::Role_H(int j, int i, bool enemy, int health, int attack_power, int attack_interval, int cost, QString name)
    : MyRole(i, j, enemy, health, attack_power, attack_interval, cost, name){
    if (this->posi >= 1)
    {
        this->Attack_area.append(gridvec(this->posi - 1, this->posj));
    }
    if (this->posi >= 2)
    {
        this->Attack_area.append(gridvec(this->posi - 2, this->posj));
    }
    if (this->posi >= 3)
    {
        this->Attack_area.append(gridvec(this->posi - 3, this->posj));
    }
    if (this->posi >= 4)
    {
        this->Attack_area.append(gridvec(this->posi - 4, this->posj));
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

void Role_H::UpdateState(Game &game)
{
    this->be_attacked();
    if(game.IsValid(GridVec(posi,posj))){
        posx-=spd;
        posi=(posx-Left_Width)/Cell_Size;
        this->Attack_area.clear();
        if (this->posi >= 1)
        {
            this->Attack_area.append(gridvec(this->posi - 1, this->posj));
        }
        if (this->posi >= 2)
        {
            this->Attack_area.append(gridvec(this->posi - 2, this->posj));
        }
        if (this->posi >= 3)
        {
            this->Attack_area.append(gridvec(this->posi - 3, this->posj));
        }
        if (this->posi >= 4)
        {
            this->Attack_area.append(gridvec(this->posi - 4, this->posj));
        }
    }
    if (this->state == 1)
    {

        if (!timer_attackcd.isActive())
        {
            this->AttackObject(&game);
            if(!this->Attack_list.empty())this->state = 2;
        }

    }
    if (this->state == 2)
    {
        this->Attack(&game);
    }


}

void Role_H::SkillBegin(Game&game) {}
void Role_H::SkillEnd() {}
void Role_H::Attack(Game *game){
    if(!is_attacking){
        is_attacking=true;
        this->timer_attacking.start(700);
        this->timer_attacking.setSingleShot(true);
        for (auto object:Attack_list){
            if(object==nullptr)continue;
            myBullet*temp=new myBullet(this->name,this->posi*Cell_Size+Left_Width+40,this->posj*Cell_Size+Up_Height,this->attack_power);
            qDebug()<<"H's bullet"<<temp->attack_power<<"list length"<<Attack_list.length();
            if(temp!=NULL)object->Bullets.push_back(temp);
        }
    }
    if(!this->timer_attacking.isActive())
    {

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
