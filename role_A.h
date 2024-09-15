#ifndef ROLE_A_H
#define ROLE_A_H
#include<myRole.h>
class Role_A:public MyRole
{
public:
    Role_A(int i,int j,bool enemy=false,int health=1500,int attack_power=500,int attack_interval=1000,int cost=8,QString name="A");
    bool skill_open=false;
    void UpdateState(Game&game)override;
    void Attack(Game *game)override;

    void SkillBegin(Game &game)override;
    void SkillEnd()override;
};

#endif // ROLE_A_H
