#ifndef ROLE_E_H
#define ROLE_E_H
#include<myRole.h>
#include<game.h>
class role_E:public MyRole
{
public:
    role_E(int i,int j,bool enemy,int health,int attack_power,int attack_interval,int cost,QString name);
    bool skill_open=false;
    void UpdateState(Game&game)override;
    void Attack(Game *game)override;
    void SkillBegin(Game &game) override;
    void SkillEnd()override;
    int temp;
};

#endif // ROLE_E_H
