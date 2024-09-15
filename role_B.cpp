
#include "role_B.h"

role_B::role_B(int i,int j,bool enemy,int health,int attack_interval,int cost,QString name)
    :MyRole( i, j, enemy, health, attack_interval,cost,name){};

void role_B::Attack(QList<MyRole*>Objects){
    for(auto object:Objects){
        myBullet*bullet=new myBullet("B",this->posi,this->posj,1000);
        object->bullets.append(bullet);
    }
}
