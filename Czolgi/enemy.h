#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QDebug>

class Enemy : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Enemy();

    void patrol(qreal end);
    qreal initx = 900;
    qreal inity = 100;

public slots:
    void move();

private:
    qreal speed = 4;

    bool reverso = false;
};

#endif // ENEMY_H
