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
    void setTexture(int angle);

    qreal speed;
    qreal view_range;

    int hp;
    int dmg;
    double armor;
    int reload_time = 2000;

    bool is_loading = false;
    bool is_rotating = false;

    int init_angle = 0;
    int rotate_angle = 0;

public slots:
    void reload();

protected:
    QString tex_path[24];
};

#endif // TANK_H
