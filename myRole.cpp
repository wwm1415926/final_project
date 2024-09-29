#include "myRole.h"
#include<QDebug>
#include<iostream>

MyRole::MyRole(int i,int j,bool enemy,int health,int attack_power,int attack_interval,int cost,QString name){
    this->posi=i;
    this->posj=j;
    this->enemy=enemy;
    this->health=health;
    this->attack_interval=attack_interval;
    this->cost=cost;
    this->name=name;
    this->attack_power=attack_power;
}

void MyRole::be_attacked(){
    for(auto bullet:this->Bullets){
        if(this->enemy){
            if(bullet->posx>=(this->posx-20)){
                this->health-=bullet->attack_power;
                Bullets.removeAll(bullet);

            }
            else bullet->posx+=5;
        }
        else{
            if(bullet->posx<=(this->posi*Cell_Size+Left_Width+20)){
                this->health-=bullet->attack_power;
                Bullets.removeAll(bullet);
            }
            else bullet->posx-=5;
        }
    }

}
void MyRole::AttackObject(Game *game)
{
    MyRole *temp;
    int distance=9999;
    if(this->enemy==false){
        for (int i = 0; i < game->EnemyRoles.size(); i++)
        {
            for (auto area : this->Attack_area)
            {
                if (game->EnemyRoles[i]->posj == area.j && game->EnemyRoles[i]->posi == area.i)
                {
                    if (game->EnemyRoles[i]->posi < distance)
                    {
                        temp = game->EnemyRoles[i];
                        distance=0;
                    }
                }
                if(distance==0)
                    this->Attack_list.append(temp);
            }
        }
    }

    else{
        for (int i = 0; i < game->OurRoles.size(); i++)
        {
            for (auto area : this->Attack_area)
            {
                if (game->OurRoles[i]->posj == area.j && game->OurRoles[i]->posi == area.i)
                {
                    if (game->OurRoles[i]->posi < distance)
                    {
                        temp = game->OurRoles[i];
                        distance=0;
                    }
                }
                if(distance==0)
                    this->Attack_list.append(temp);
            }
        }
    }

}
MyRole::~MyRole(){
    for (auto it = this->Bullets.begin(); it != this->Bullets.end();) {
        it = this->Bullets.erase(it);
    }

    this->Bullets.clear();  // 清空容器，移除所有指针
    this->Attack_area.clear();
    this->Attack_list.clear();

}


