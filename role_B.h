#ifndef ROLE_B_H
#define ROLE_B_H
#include<myRole.h>
#include<game.h>
class role_B:public MyRole
{
public:
    role_B(int i,int j,bool enemy,int health,int attack_interval,int cost,QString name);
    void UpdateState(Game&game)override;

};

#endif // ROLE_B_H
