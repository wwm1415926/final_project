#ifndef ROLE_A_H
#define ROLE_A_H
#include<myRole.h>
class Role_A:public MyRole
{
public:
   Role_A(int i,int j,bool enemy,int health,double attack_interval,int cost,QString name);
   void UpdateState(Game&game)override;
};

#endif // ROLE_A_H
