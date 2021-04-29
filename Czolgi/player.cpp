#include "player.h"
#include <math.h>
#include "bullet.h"

Player::Player()
{
    //sc = scene;
    this->setPixmap(QPixmap(":/img/tex/tex_player_01.png"));
    this->setTransformOriginPoint(25,25);
}

void Player::setPlayerName(QString Pname)
{
    name = Pname;
    qDebug()<<name;
}

void Player::shot()
{
    if(bullets)
        bullets = bullets - 1;
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

    if(event->key() == Qt::Key_Space)
    {
        if(bullets)
        {
            Bullet *bullet = new Bullet();
            bullet->setPos(x()+50,y()+32);
            scene()->addItem(bullet);
            shot();
        }

        else
        {
            qDebug()<<"Koniec pocisków RAMBO!!!";
        }
    }
    qDebug()<<this->x()<<this->y();
}
