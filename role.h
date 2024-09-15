#ifndef ROLE_H
#define ROLE_H

#include <QObject>
#include<game.h>
class Item : public QObject
{
    Q_OBJECT
public:
    QString name;
    int posx,posy;
    int celli,cellj;//位置和网格，要注意左上角为原点，自左向右为x轴，自上向下为y轴
    int health;
    int cost;
    int attack_val;
    int attack_interval;

public:
    virtual void attack() = 0;
public:
    explicit Item(QObject *parent = nullptr);


signals:
};

#endif // ROLE_H
