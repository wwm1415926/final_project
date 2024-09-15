#include "myRole.h"
#include<QDebug>
#include<iostream>
MyRole::MyRole(int i,int j,bool enemy,int health,int attack_interval,int cost,QString name){
    this->posi=i;
    this->posj=j;
    this->enemy=enemy;
    this->health=health;
    this->attack_interval=attack_interval;
    this->cost=cost;
    this->name=name;
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
