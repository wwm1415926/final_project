#ifndef ROLE_K_H
#define ROLE_K_H
#include <myRole.h>
class Role_K : public MyRole
{
public:
    int speed = 1;
    Role_K(int j, int i = 11, bool enemy = true, int health = 10000, int attack_power = 700, int attack_interval = 3000, int cost = 0, QString name = "K");
    bool attack_cd = false;
    void UpdateState(Game &game) override;
    void Attack(Game *game) override;
    void SkillBegin(Game&game) override;
    void SkillEnd() override;
};

#endif // ROLE_K_H
