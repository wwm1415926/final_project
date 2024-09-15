#ifndef MINE_H
#define MINE_H

#include <QObject>
#include<QTimerEvent>
class Mine : public QObject
{
    Q_OBJECT
public:
    explicit Mine(QObject *parent = nullptr);
    int speed;
    int PosX,PosY;
    Mine(int x,int y,int speed){
        PosX=x;
        PosY=y;
        this->speed=speed;
    }

signals:
private slots:
    void MineSpawn();
protected:

};

#endif // MINE_H
