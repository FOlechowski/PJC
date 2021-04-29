#include "player.h"
#include <math.h>

Player::Player()
{
    this->setPixmap(QPixmap(":/img/img/icon.png"));
    this->setTransformOriginPoint(25,25);
}

void Player::setPlayerName(QString Pname)
{
    name = Pname;
    qDebug()<<name;
}

void Player::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_A)
    {
        setPos(x()-speed,y());
        //angle -= 10;
        //setRotation(angle);
    }
    if(event->key() == Qt::Key_D)
    {
        setPos(x()+speed,y());
        //angle += 10;
        //setRotation(angle);
    }

    if(event->key() == Qt::Key_W)
    {
        setPos(x(),y()-speed);
    }
    if(event->key() == Qt::Key_S)
    {
        setPos(x(),y()+speed);
    }
    qDebug()<<this->x()<<this->y();
}
