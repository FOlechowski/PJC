#include "tank.h"
#include "bullet.h"
#include <QGraphicsScene>
#include <QDebug>
#include <cmath>

Tank::Tank()
{
}

void Tank::shot(float angle)
{
    if(!is_loading && !is_rotating)
    {
        timer_reload->start(reload_time);
        is_loading = true;
        Bullet *bullet = new Bullet(angle, this);
        bullet->setPos(x()+35,y()+50);
        scene()->addItem(bullet);
    }
}

void Tank::move(qreal dx, qreal dy)
{
    setPos(x()+dx,y()+dy);
}

void Tank::setTexture(int angle )
{
    switch (angle)
    {
        case 0:
        this->setPixmap(QPixmap(tex_path[0]));
        break;

        case 15:
        this->setPixmap(QPixmap(tex_path[1]));
        break;

        case 30:
        this->setPixmap(QPixmap(tex_path[2]));
        break;

        case 45:
        this->setPixmap(QPixmap(tex_path[3]));
        break;

        case 60:
        this->setPixmap(QPixmap(tex_path[4]));
        break;

        case 75:
        this->setPixmap(QPixmap(tex_path[5]));
        break;

        case 90:
        this->setPixmap(QPixmap(tex_path[6]));
        break;

        case 105:
        this->setPixmap(QPixmap(tex_path[7]));
        break;

        case 120:
        this->setPixmap(QPixmap(tex_path[8]));
        break;

        case 135:
        this->setPixmap(QPixmap(tex_path[9]));
        break;

        case 150:
        this->setPixmap(QPixmap(tex_path[10]));
        break;

        case 165:
        this->setPixmap(QPixmap(tex_path[11]));
        break;

        case 180:
        this->setPixmap(QPixmap(tex_path[12]));
        break;

        case -15:
        this->setPixmap(QPixmap(tex_path[13]));
        break;

        case -30:
        this->setPixmap(QPixmap(tex_path[14]));
        break;

        case -45:
        this->setPixmap(QPixmap(tex_path[15]));
        break;

        case -60:
        this->setPixmap(QPixmap(tex_path[16]));
        break;

        case -75:
        this->setPixmap(QPixmap(tex_path[17]));
        break;

        case -90:
        this->setPixmap(QPixmap(tex_path[18]));
        break;

        case -105:
        this->setPixmap(QPixmap(tex_path[19]));
        break;

        case -120:
        this->setPixmap(QPixmap(tex_path[20]));
        break;

        case -135:
        this->setPixmap(QPixmap(tex_path[21]));
        break;

        case -150:
        this->setPixmap(QPixmap(tex_path[22]));
        break;

        case -165:
        this->setPixmap(QPixmap(tex_path[23]));
        break;
    }
}

void Tank::reload()
{
    timer_reload->stop();
    is_loading = false;
}
