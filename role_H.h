#ifndef ROLE_H_H
#define ROLE_H_H
#include <myRole.h>
class Role_H : public MyRole
{
public:
    int speed = 1;
    Role_H(int j, int i = 11, bool enemy = true, int health = 1850, int attack_power= 100,
           int attack_interval = 2000, int cost = 0, QString name = "H");

    bool attack_cd = false;
    void UpdateState(Game &game) override;
    void Attack(Game *game) override;
    void SkillBegin(Game&game) override;
    void SkillEnd() override;
};

#endif // ROLE_H_H
