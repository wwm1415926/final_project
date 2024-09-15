#ifndef ROLE_A_H
#define ROLE_A_H
#include<myRole.h>
class Role_A:public MyRole
{
public:
    Role_A(int i,int j,bool enemy,int health,int attack_power,int attack_interval,int cost,QString name);
    bool skill_open=false;
    void UpdateState(Game&game)override;
    void Attack(Game *game)override;
    void SkillBegin(Game &game) override;
    void SkillEnd()override;
};

#endif // ROLE_A_H
