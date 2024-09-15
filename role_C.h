#ifndef ROLE_C_H
#define ROLE_C_H
#include<myRole.h>
#include<game.h>
class role_C:public MyRole
{
public:
    role_C(int i,int j,bool enemy,int health,int attack_power,int attack_interval,int cost,QString name);
    bool skill_open=false;
    void UpdateState(Game&game)override;
    void Attack(Game *game)override;
    void SkillBegin(Game &game) override;
    void SkillEnd()override;
};

#endif // ROLE_C_H
