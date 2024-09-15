#ifndef ROLE_D_H
#define ROLE_D_H
#include<myRole.h>
#include<game.h>
class role_D:public MyRole
{
public:
    role_D(int i,int j,bool enemy=false,int health=1700,int attack_power=1000,int attack_interval=2400,int cost=24,QString name="D");
    bool skill_open=false;
    void UpdateState(Game&game)override;
    void Attack(Game *game)override;
    void SkillBegin(Game &game) override;
    void SkillEnd()override;
    int temp;
};
#endif // ROLE_D_H
