#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include "tank.h"
#include "game.h"

class Bullet: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Bullet(float ang, Tank* tank);
    Bullet();

private slots:
    void moveBullet();

protected:
    bool checkIfEnemy(QGraphicsItem *colliding_item);
    virtual bool bulletIsCollidig();
    bool bounce();

    qreal speed = 8;
    int penetration = 100;
    float angle;
    Tank* creator;
    Tank* hitted;
private:
    Game* game;
};

#endif // BULLET_H
