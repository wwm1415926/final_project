#ifndef ROLE_I_H
#define ROLE_I_H
#include <myRole.h>
class Role_I : public MyRole
{
public:
    int speed = 1;
    Role_I(int j, int i = 11, bool enemy = true, int health = 16000, int attack_power= 220, int attack_interval = 2500, int cost = 0, QString name = "I");
    bool attack_cd = false;
    void UpdateState(Game &game) override;
    void Attack( Game *game) override;
    void SkillBegin(Game&game) override;
    void SkillEnd() override;
};

#endif // ROLE_I_H
