#ifndef ROLE_G_H
#define ROLE_G_H
#include <myRole.h>
class Role_G : public MyRole
{
public:
    int speed = 1;
    Role_G(int j, int i = 11, bool enemy = true, int health = 1050, int attack = 150, int attack_interval = 1200, int cost = 0, QString name = "G");
    QTimer *timer_attacking = new QTimer(this);
    QTimer *timer_attack_interval = new QTimer(this);
    bool attack_cd = false;
    void UpdateState(Game &game) override;
    void Attack( Game *game) override;
    void SkillBegin(Game&game) override;
    void SkillEnd() override;
};

#endif // ROLE_G_H
