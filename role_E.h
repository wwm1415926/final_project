#ifndef ROLE_E_H
#define ROLE_E_H
#include<myRole.h>
#include<game.h>
class role_E:public MyRole
{
public:
    role_E(int i,int j,bool enemy,int health,int attack_interval,int cost,QString namen);
    bool CanPlace(GridVec click,Game&game)override;
    void UpdateState(Game&game)override;
};

#endif // ROLE_E_H
