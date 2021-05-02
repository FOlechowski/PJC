#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include "tank.h"

class Bullet: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Bullet(float ang, Tank* tank );

public slots:
    void move();

private:
    qreal speed = 5;
    float angle;
    Tank* creator;
    Tank* hitted;
};

#endif // BULLET_H
