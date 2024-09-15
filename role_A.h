#ifndef ROLE_A_H
#define ROLE_A_H
#include<myRole.h>
class Role_A:public MyRole
{
public:
    Role_A(int i,int j,bool enemy,int health,int attack,int attack_interval,int cost,QString name);
    QTimer *timer1;
    QTimer *timer2;
    QTimer *timer3;
    QTimer *timer4;
    bool attack_cd=false;
   void UpdateState(Game&game)override;
};

#endif // ROLE_A_H
