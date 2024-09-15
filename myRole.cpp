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

