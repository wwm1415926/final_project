#ifndef ROLE_C_H
#define ROLE_C_H
#include<myRole.h>
#include<game.h>
class role_C:public MyRole
{
public:
    role_C(int i,int j,bool enemy,int health,int attack_interval,int cost,QString name);
    void UpdateState(Game&game)override;
};

#endif // ROLE_C_H
