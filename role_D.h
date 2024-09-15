#ifndef ROLE_D_H
#define ROLE_D_H
#include<myRole.h>
#include<game.h>
class role_D:public MyRole
{
public:
    role_D(int i,int j,bool enemy,int health,int attack_power,int attack_interval,int cost,QString name);
    bool skill_open=false;
    void UpdateState(Game&game)override;
    void Attack(Game *game)override;
    void SkillBegin(Game &game) override;
    void SkillEnd()override;
    int temp;
};
#endif // ROLE_D_H
