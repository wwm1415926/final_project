#ifndef ROLE_J_H
#define ROLE_J_H
#include <myRole.h>
class Role_J : public MyRole
{
public:
    int speed = 1;
    Role_J(int j, int i = 11, bool enemy = true, int health = 6000, int attack = 600, int attack_interval = 2600, int cost = 0, QString name = "J");
    QTimer *timer_attacking = new QTimer(this);
    QTimer *timer_attack_interval = new QTimer(this);
    bool attack_cd = false;
    void UpdateState(Game &game) override;
    void AttackObject(Game *game) override;
    void Attack(QList<MyRole *> Objects, Game *game) override;
    void SkillBegin() override;
    void SkillEnd() override;
};

#endif // ROLE_J_H
