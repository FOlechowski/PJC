#include "tank.h"
#include "bullet.h"
#include <QGraphicsScene>

Tank::Tank()
{

}

void Tank::shot(float angle)
{
    if(!is_loading)
    {
        timer_reload->start(2000);
        is_loading = true;
        Bullet *bullet = new Bullet(angle, this);
        bullet->setPos(x()+50,y()+50);
        scene()->addItem(bullet);

    }
}

void Tank::reload()
{
    timer_reload->stop();
    is_loading = false;
}
