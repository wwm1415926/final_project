#ifndef ROLE_K_H
#define ROLE_K_H
#include <myRole.h>
class Role_K : public MyRole
{
public:
    int speed = 1;
    Role_K(int j, int i = 11, bool enemy = true, int health = 10000, int attack = 700, int attack_interval = 3000, int cost = 0, QString name = "K");
    QTimer *timer_attacking = new QTimer(this);
    QTimer *timer_attack_interval = new QTimer(this);
    bool attack_cd = false;
    void UpdateState(Game &game) override;
    void AttackObject(Game *game) override;
    void Attack(QList<MyRole *> Objects, Game *game) override;
    void SkillBegin() override;
    void SkillEnd() override;
};

#endif // ROLE_K_H
