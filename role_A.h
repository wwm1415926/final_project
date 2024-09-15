#ifndef ROLE_A_H
#define ROLE_A_H
#include<myRole.h>
class Role_A:public MyRole
{
public:
    Role_A(int i,int j,bool enemy,int health,int attack,int attack_interval,int cost,QString name);
    QTimer *timer_attacking=new QTimer(this);
    QTimer *timer_attack_interval=new QTimer(this);
    bool attack_cd=false;
    void UpdateState(Game&game)override;
    void AttackObject(Game*game)override;
    void Attack(QList<MyRole*>Objects,Game *game)override;
    void SkillBegin() override;
    void SkillEnd()override;
};

#endif // ROLE_A_H
