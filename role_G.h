#ifndef ROLE_G_H
#define ROLE_G_H
#include <myRole.h>
#include <mybullet.h>
class Role_G : public MyRole
{
public:
   double posx, posy;
   Role_G(int i = 11, int j, bool enemy = 1, int health = 1050, int attack = 150, int attack_interval = 1200, double speed = 1, int cost = 0, QString name = "G");
   void UpdateState(Game &game) override;

   bool stop();
   /*
    *根据坐标和敌我，确定范围内的攻击对象
    */

   QList<MyRole *> AttackObject(int i, int j, bool enemy = 0) override;

   /*
    * 对范围内所有目标发起攻击;如果是近战就改变显示形态并让目标内的敌人频闪一下
    * 如果是远程，就要创立bullet对象？
    */
   void Attack(QList<MyRole *> Objects) override;

   void be_attacked(int) override;
};

#endif // ROLE_G_H
