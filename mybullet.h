#ifndef MYBULLET_H
#define MYBULLET_H

#include <QObject>

class myBullet : public QObject
{
    Q_OBJECT
public:
    explicit myBullet(QObject *parent = nullptr);

signals:
};

#endif // MYBULLET_H
