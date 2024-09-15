
#include "role_B.h"

role_B::role_B(int i,int j,bool enemy,int health,int attack_interval,int cost,QString name)
    :MyRole( i, j, enemy, health, attack_interval,cost,name){};

void role_B::Attack(QList<MyRole*>Objects){
    this->timer_attacking->start(500);
    for (auto object:Attack_list){
        myBullet*temp=new myBullet(this->name,this->posi,this->posj,this->attack_power);
        object->Bullets.append(temp);
    }
    connect(timer_attacking,&QTimer::timeout,this,[=]{
        timer_attacking->stop();
        if(this->timer_skilling.isActive())this->state=3;
        this->state=1;
        timer_attack_interval->start(this->attack_interval);
        for (auto object:Attack_list){
            object->be_attacking=false;
            Attack_list.pop_back();
        }
    });
}
