#ifndef ROLE_G_H
#define ROLE_G_H
#include <myRole.h>
class Role_G : public MyRole
{
public:
    Role_G(int j, int i = 11, bool enemy = true, int health = 1050, int attack_power= 150, int attack_interval = 1200, int cost = 0, QString name = "G");
    void UpdateState(Game &game) override;
    void Attack( Game *game) override;
    void SkillBegin(Game&game) override;
    void SkillEnd() override;
};

#endif // ROLE_G_H
