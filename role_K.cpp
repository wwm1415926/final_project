#include "role_K.h"

Role_K::Role_K(int j, int i, bool enemy, int health, int attack_power, int attack_interval, int cost, QString name)
    : MyRole(i, j, enemy, health, attack_power, attack_interval, cost, name){
    this->Attack_area.append(GridVec(this->posi, this->posj));
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

void Role_K::UpdateState(Game &game)
{
    this->be_attacked();
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

    if(game.IsValid(GridVec(posi,posj))){
        posx-=spd;
        posi=(posx-Left_Width)/Cell_Size;
        this->Attack_area.clear();
        this->Attack_area.append(GridVec(this->posi, this->posj));
        this->Attack_area.append(gridvec(this->posi-1,this->posj));
    }
}
void Role_K::SkillBegin(Game&game) {}

void Role_K::SkillEnd() {}
void Role_K::Attack(Game *game)
{
    if(!this->is_attacking)
    {
        this->is_attacking=true;
        this->timer_attacking.start(700);
        this->timer_attacking.setSingleShot(true);
        for (auto object:Attack_list){
            if(object==nullptr)continue;
            object->be_attacking=true;
            object->health-=this->attack_power;
        }
    }
    if(!this->timer_attacking.isActive())
    {

        this->state=1;
        this->is_attacking=false;
        this->timer_attacking.start(this->attack_interval);
        this->timer_attacking.setSingleShot(true);
        for (auto object:Attack_list){
            object->be_attacking=false;
            Attack_list.pop_back();
        }
         Attack_list.clear();
    }
}
