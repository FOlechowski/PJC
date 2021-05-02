#ifndef TANK_H
#define TANK_H

#include <QObject>
#include <QTimer>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

class Tank : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Tank();

    QTimer *timer_reload = new QTimer;

    void shot(float angle);
    void move(qreal dx, qreal dy);

    qreal speed;
    qreal view_range;

    int hp;
    int dmg;
    double armor;
    int reload_time = 2000;

    bool is_loading = false;

public slots:
    void reload();

protected:
};

#endif // TANK_H
