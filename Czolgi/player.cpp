#include "player.h"
#include <cmath>
#include "bullet.h"


Player::Player()
{
    //sc = scene;
    this->setPixmap(QPixmap(":/img/tex/tex_player_01.png"));

    connect(timer_reload, SIGNAL(timeout()),this,SLOT(reload()));

    speed = 5;

    this->installEventFilter(this);
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

        angle += 5;
        //setRotation(angle);
    }

    if(event->key() == Qt::Key_D)
    {

        angle -= 5;
        //setRotation(angle);
    }

    if(event->key() == Qt::Key_W)
    {
        Tank::move(cos(angle*M_PI/180)*speed,-sin(angle*M_PI/180)*speed);

    }

    if(event->key() == Qt::Key_S)
    {
        Tank::move(-cos(angle*M_PI/180)*speed,sin(angle*M_PI/180)*speed);
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
    qDebug()<<angle;
}

