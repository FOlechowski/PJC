#include "player.h"
#include <cmath>
#include "bullet.h"


Player::Player()
{
    //sc = scene;
    this->setPixmap(QPixmap(":/img/tex/tex_player_01.png"));
    this->setTransformOriginPoint(25,25);

    connect(timer_reload, SIGNAL(timeout()),this,SLOT(reload()));

    speed = 5;
}

void Player::setPlayerName(QString Pname)
{
    name = Pname;
    qDebug()<<name;
}

void Player::shot()
{
    if(bullets && !is_loading)
    {
        timer_reload->start(2000);

        is_loading = true;
        bullets = bullets - 1;
    }
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
        if(bullets && !is_loading)
        {
            Bullet *bullet = new Bullet(0, this);
            bullet->setPos(x()+50,y()+35);
            scene()->addItem(bullet);
            shot();
        }

        else
        {
            qDebug()<<"Koniec pocisków RAMBO!!!";
        }
    }
    //qDebug()<<this->x()<<this->y();
}

