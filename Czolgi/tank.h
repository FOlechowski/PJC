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
    ~Tank();
    void shot(float angle);
    void move(qreal dx, qreal dy);
    void setTexture(int angle);

    void modifyHP(int dmg, int penetration);
    int getDMG();
    int getHP();
    void setHP(int hp);
    void setInitialParameters(int hp, int dmg, float armor);
    void getParameters(float *armor, int *rotation_angle);

public slots:
    void reload();

protected:
    QString tex_path[24];

    qreal speed;
    qreal view_range;

    int hp;
    int dmg;
    float armor;
    int reload_time = 2000;

    bool is_loading = false;
    bool is_rotating = false;

    int rotate_angle = -1000;

    QTimer *timer_reload = new QTimer(this);
};

#endif // TANK_H
