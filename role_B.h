#ifndef ROLE_B_H
#define ROLE_B_H
#include<myRole.h>
#include<game.h>
class role_B:public MyRole
{
public:
    role_B(int i,int j,bool enemy=false,int health=1800,int attack_power=900,int attack_interval=2900,int cost=30,QString name="B");
    bool skill_open=false;
    void UpdateState(Game&game)override;
    void Attack(Game *game)override;
    void SkillBegin(Game &game) override;
    void SkillEnd()override;
    int temp;
};

#endif // ROLE_B_H
