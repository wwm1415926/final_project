#include "mybullet.h"



myBullet::myBullet(){}
myBullet::myBullet(QString name,int x,int y,int attack_power){
    this->name=name;
    this->posx=x;
    this->posy=y;
    this->attack_power=attack_power;
    this->is_attacking=true;
}
