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
                myBullet*temp=bullet;
                this->Bullets.pop_back();
                delete temp;
            }
            else bullet->posx+=5;
        }
        else{
            if(bullet->posx<=(this->posx+20)){
                this->health-=bullet->attack_power;
                myBullet*temp=bullet;
                this->Bullets.pop_back();
                delete temp;
            }
            else bullet->posy+=5;
        }
    }

}
void MyRole::AttackObject(Game *game)
{
    MyRole *temp;
    int distance=9999;
    for (int i = 0; i < game->EnemyRoles.size(); i++)
    {
        for (auto area : this->Attack_area)
        {
            if (game->EnemyRoles[i]->posj == area.j && game->EnemyRoles[i]->posi == area.j)
            {
                if (game->EnemyRoles[i]->posi < distance)
                    temp = game->EnemyRoles[i];
            }
            if(temp!=NULL)this->Attack_list.append(temp);
        }
    }
}
