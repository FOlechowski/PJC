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
    bool is_loading = false;

    void shot(float angle);
    void move();

    qreal speed;
    qreal view_range;

    int hp;
    int dmg;

    double armor;

public slots:
    void reload();
private:

};

#endif // TANK_H
