#ifndef ROLE_E_H
#define ROLE_E_H
#include<myRole.h>
#include<game.h>
class role_E:public MyRole
{
public:
    role_E(int i,int j,bool enemy=false,int health=3500,int attack_power=900,int attack_interval=1600,int cost=25,QString name="E");
    bool skill_open=false;
    void UpdateState(Game&game)override;
    void Attack(Game *game)override;
    void SkillBegin(Game &game) override;
    void SkillEnd()override;
    int temp;
};

#endif // ROLE_E_H
