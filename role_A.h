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
    QList<MyRole*>AttackObject(int i,int j,bool enemy)override;
    void AttackObject2(Game &game)override;
    void Attack(QList<MyRole*>Objects,Game &game)override;
    QList<MyRole*>Attack_list;
};

#endif // ROLE_A_H
