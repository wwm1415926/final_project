#ifndef ROLE_D_H
#define ROLE_D_H
#include<myRole.h>
#include<game.h>
class role_D:public MyRole
{
public:
    role_D(int i,int j,bool enemy,int health,int attack_interval,int cost,QString name);
    void UpdateState(Game&game)override;
};
#endif // ROLE_D_H
