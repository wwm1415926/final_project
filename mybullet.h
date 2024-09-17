#ifndef MYBULLET_H
#define MYBULLET_H

#include <QObject>

class myBullet : public QObject
{
    Q_OBJECT
public:
    int posx;
    int posy;
    QString name;
    myBullet();
    myBullet(QString name,int x,int y,int attack_power);
    int attack_power;
    bool is_attacking;
};

#endif // MYBULLET_H
