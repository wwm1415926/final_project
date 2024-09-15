#ifndef ROLE_F_H
#define ROLE_F_H

#include<myRole.h>
#include<game.h>
class role_F:public MyRole
{
public:
    role_F(int i,int j,bool enemy=false,int health=1650,int attack_power=0,int attack_interval=0,int cost=13,QString name="F");
    bool skill_open=false;
    void UpdateState(Game&game)override;
    void Attack(Game *game)override;
    void SkillBegin(Game &game) override;
    void SkillEnd()override;
    int temp;
};

#endif // ROLE_F_H
