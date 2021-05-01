#include "tank.h"
#include "bullet.h"
#include <QGraphicsScene>

Tank::Tank()
{

}

void Tank::shot(qreal dx, qreal dy)
{
    if(!is_loading)
    {
        timer_reload->start(2000);
        is_loading = true;
        Bullet *bullet = new Bullet();
        bullet->setPos(x()+100,y()+32);
        scene()->addItem(bullet);

    }
}

void Tank::reload()
{
    timer_reload->stop();
    is_loading = false;
}
