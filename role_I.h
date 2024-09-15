#ifndef ROLE_I_H
#define ROLE_I_H
#include <myRole.h>
class Role_I : public MyRole
{
public:
    int speed = 1;
    Role_I(int j, int i = 11, bool enemy = true, int health = 1600, int attack = 220, int attack_interval = 2500, int cost = 0, QString name = "I");
    QTimer *timer_attacking = new QTimer(this);
    QTimer *timer_attack_interval = new QTimer(this);
    bool attack_cd = false;
    void UpdateState(Game &game) override;
    void AttackObject(Game *game) override;
    void Attack(QList<MyRole *> Objects, Game *game) override;
    void SkillBegin() override;
    void SkillEnd() override;
};

#endif // ROLE_I_H
