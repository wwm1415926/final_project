#ifndef ROLE_G_H
#define ROLE_G_H
#include <myRole.h>
#include <mybullet.h>
class Role_G : public MyRole
{
public:
    int posx, posy;
    int spd;
   Role_G(int j,int i, bool enemy, int health ,
          int attack , int attack_interval, int  spd, int cost, QString name );
   void UpdateState(Game &game) override;

   bool stop();
   /*
    *根据坐标和敌我，确定范围内的攻击对象
    */


   QList<MyRole *> AttackObject(int i, int j, bool enemy = 0,Game *game) override;

   /*
    * 对范围内所有目标发起攻击;如果是近战就改变显示形态并让目标内的敌人频闪一下
    * 如果是远程，就要创立bullet对象？
    */
   void Attack(QList<MyRole *> Objects) override;

   void be_attacked_near(int);
   void be_attacked_far(myBullet*);


};

#endif // ROLE_G_H
