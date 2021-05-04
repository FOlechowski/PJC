#include "player.h"
#include <cmath>
#include "bullet.h"


Player::Player()
{
    this->setPixmap(QPixmap(":/img/tex/arrow_p0.png"));

    connect(timer_reload, SIGNAL(timeout()),this,SLOT(reload()));

    speed = 5;
    addPlayerTextures();


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
    QList<QGraphicsItem*> colliding_items = collidingItems();
    qDebug()<<colliding_items;
    //grabKeyboard();
    if(event->key() == Qt::Key_A)
    {

        rotate_angle += 15;
        if(rotate_angle>180)
        {
            rotate_angle=-165;
        }

    }

    if(event->key() == Qt::Key_D)
    {

        rotate_angle -= 15;
        if(rotate_angle<-180)
        {
            rotate_angle=165;
        }

    }

    if(event->key() == Qt::Key_W)
    {
        Tank::move(cos(rotate_angle*M_PI/180)*speed,-sin(rotate_angle*M_PI/180)*speed);

    }

    if(event->key() == Qt::Key_S)
    {
        Tank::move(-cos(rotate_angle*M_PI/180)*speed,sin(rotate_angle*M_PI/180)*speed);
    }



    if(event->key() == Qt::Key_Space)
    {
        if(bullets && !is_loading)
        {
            Bullet *bullet = new Bullet(-rotate_angle*M_PI/180, this);
            bullet->setPos(x()+50,y()+35);
            scene()->addItem(bullet);
            shot();
        }

        else
        {
            qDebug()<<"Koniec pocisków RAMBO!!!";
        }
    }
    //qDebug()<<(int(-rotate_angle)%360);


        switch (int(-rotate_angle))
        {
            case 0:
            this->setPixmap(QPixmap(PlayerTextures[0]));
            break;

            case 15:
            this->setPixmap(QPixmap(PlayerTextures[1]));
            break;

            case 30:
            this->setPixmap(QPixmap(PlayerTextures[2]));
            break;

            case 45:
            this->setPixmap(QPixmap(PlayerTextures[3]));
            break;

            case 60:
            this->setPixmap(QPixmap(PlayerTextures[4]));
            break;

            case 75:
            this->setPixmap(QPixmap(PlayerTextures[5]));
            break;

            case 90:
            this->setPixmap(QPixmap(PlayerTextures[6]));
            break;

            case 105:
            this->setPixmap(QPixmap(PlayerTextures[7]));
            break;


            case 120:
            this->setPixmap(QPixmap(PlayerTextures[8]));
            break;

            case 135:
            this->setPixmap(QPixmap(PlayerTextures[9]));
            break;

            case 150:
            this->setPixmap(QPixmap(PlayerTextures[10]));
            break;

            case 165:
            this->setPixmap(QPixmap(PlayerTextures[11]));
            break;

            case 180:
            this->setPixmap(QPixmap(PlayerTextures[12]));
            break;

            case -180:
            this->setPixmap(QPixmap(PlayerTextures[12]));
            break;

            case -15:
            this->setPixmap(QPixmap(PlayerTextures[13]));
            break;

            case -30:
            this->setPixmap(QPixmap(PlayerTextures[14]));
            break;

            case -45:
            this->setPixmap(QPixmap(PlayerTextures[15]));
            break;

            case -60:
            this->setPixmap(QPixmap(PlayerTextures[16]));
            break;

            case -75:
            this->setPixmap(QPixmap(PlayerTextures[17]));
            break;

            case -90:
            this->setPixmap(QPixmap(PlayerTextures[18]));
            break;

            case -105:
            this->setPixmap(QPixmap(PlayerTextures[19]));
            break;

            case -120:
            this->setPixmap(QPixmap(PlayerTextures[20]));
            break;

            case -135:
            this->setPixmap(QPixmap(PlayerTextures[21]));
            break;

            case -150:
            this->setPixmap(QPixmap(PlayerTextures[22]));
            break;

            case -165:
            this->setPixmap(QPixmap(PlayerTextures[23]));
            break;

    }
}

void Player::keyReleaseEvent(QKeyEvent *event)
{

}

void Player::addPlayerTextures(){
    PlayerTextures[0] = ":/img/tex/arrow_p0.png";
    PlayerTextures[1] = ":/img/tex/arrow_p15.png";
    PlayerTextures[2] = ":/img/tex/arrow_p30.png";
    PlayerTextures[3] = ":/img/tex/arrow_p45.png";
    PlayerTextures[4] = ":/img/tex/arrow_p60.png";
    PlayerTextures[5] = ":/img/tex/arrow_p75.png";
    PlayerTextures[6] = ":/img/tex/arrow_p90.png";
    PlayerTextures[7] = ":/img/tex/arrow_p105.png";
    PlayerTextures[8] = ":/img/tex/arrow_p120.png";
    PlayerTextures[9] = ":/img/tex/arrow_p135.png";
    PlayerTextures[10] = ":/img/tex/arrow_p150.png";
    PlayerTextures[11] = ":/img/tex/arrow_p165.png";
    PlayerTextures[12] = ":/img/tex/arrow_p180.png";
    PlayerTextures[13] = ":/img/tex/arrow_p-15.png";
    PlayerTextures[14] = ":/img/tex/arrow_p-30.png";
    PlayerTextures[15] = ":/img/tex/arrow_p-45.png";
    PlayerTextures[16] = ":/img/tex/arrow_p-60.png";
    PlayerTextures[17] = ":/img/tex/arrow_p-75.png";
    PlayerTextures[18] = ":/img/tex/arrow_p-90.png";
    PlayerTextures[19] = ":/img/tex/arrow_p-105.png";
    PlayerTextures[20] = ":/img/tex/arrow_p-120.png";
    PlayerTextures[21] = ":/img/tex/arrow_p-135.png";
    PlayerTextures[22] = ":/img/tex/arrow_p-150.png";
    PlayerTextures[23] = ":/img/tex/arrow_p-165.png";

}

