#include "player.h"
#include <cmath>
#include "bullet.h"
#include "explosivebullet.h"


Player::Player()
{
    this->setPixmap(QPixmap(":/img/tex/arrow_p0.png"));

    connect(timer_reload, SIGNAL(timeout()),this,SLOT(reload()));

    speed = 5;
    addPlayerTextures();
    rotate_angle = 0;
    keyA = keyW = keyD = keyS = false;


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
        timer_reload->start(reload_time);

        is_loading = true;
        bullets = bullets - 1;
    }
}

void Player::moveForward(qreal m_distance, int m_angle)
{
    keyW = true;
    Tank::move(cos(m_angle*M_PI/180)*m_distance,-sin(m_angle*M_PI/180)*m_distance);
}

void Player::moveBackward(qreal m_distance, int m_angle)
{
    keyS = true;
    Tank::move(-cos(m_angle*M_PI/180)*m_distance,sin(m_angle*M_PI/180)*m_distance);
}

void Player::turnLeft(int &m_angle)
{
    keyA = true;
    m_angle += 5;
    if(m_angle>180)
    {
        m_angle=-175;
    }
}

void Player::turnRight(int &m_angle)
{
    keyD = true;
    m_angle -= 5;
    if(m_angle<-180)
    {
        m_angle=175;
    }
}


void Player::keyPressEvent(QKeyEvent *event)
{
    QList<QGraphicsItem*> colliding_items = collidingItems();
    //qDebug()<<colliding_items;
    //grabKeyboard();
    if(event->key() == Qt::Key_A)
    {
        if(keyW){
            turnLeft(rotate_angle);
            moveForward(speed,rotate_angle);

        }else if(keyS){
            turnLeft(rotate_angle);
            moveBackward(speed,rotate_angle);

        }else{
        turnLeft(rotate_angle);
        }
    }

    if(event->key() == Qt::Key_D)
    {
        if(keyW){
            turnRight(rotate_angle);
            moveForward(speed,rotate_angle);

        }else if(keyS){
            turnRight(rotate_angle);
            moveBackward(speed,rotate_angle);

        }else{
        turnRight(rotate_angle);
        }
    }

    if(event->key() == Qt::Key_W)
    {
        if(keyA){
            moveForward(speed,rotate_angle);
            turnLeft(rotate_angle);
        }else if(keyD){
            moveForward(speed,rotate_angle);
            turnRight(rotate_angle);
        }else{
        moveForward(speed,rotate_angle);
        }
    }

    if(event->key() == Qt::Key_S)
    {
        if(keyA){
            moveBackward(speed,rotate_angle);
            turnLeft(rotate_angle);
        }else if(keyD){
            moveBackward(speed,rotate_angle);
            turnRight(rotate_angle);
        }else{
        moveBackward(speed,rotate_angle);
        }
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
    //qDebug()<<this->pos();
    qDebug()<<rotate_angle;

Tank::setTexture(-rotate_angle);

}
void Player::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_W){
        keyW = false;
        //qDebug()<<"released W";
    }
    if(event->key() == Qt::Key_D){
        keyD = false;
        //qDebug()<<"released D";
    }
    if(event->key() == Qt::Key_A){
        keyA = false;
        //qDebug()<<"released A";
    }
    if(event->key() == Qt::Key_S){
        keyS = false;
        //qDebug()<<"released S";
    }
}

void Player::addPlayerTextures(){
    tex_path[0] = ":/img/tex/arrow_p0.png";
    tex_path[1] = ":/img/tex/arrow_p15.png";
    tex_path[2] = ":/img/tex/arrow_p30.png";
    tex_path[3] = ":/img/tex/arrow_p45.png";
    tex_path[4] = ":/img/tex/arrow_p60.png";
    tex_path[5] = ":/img/tex/arrow_p75.png";
    tex_path[6] = ":/img/tex/arrow_p90.png";
    tex_path[7] = ":/img/tex/arrow_p105.png";
    tex_path[8] = ":/img/tex/arrow_p120.png";
    tex_path[9] = ":/img/tex/arrow_p135.png";
    tex_path[10] = ":/img/tex/arrow_p150.png";
    tex_path[11] = ":/img/tex/arrow_p165.png";
    tex_path[12] = ":/img/tex/arrow_p180.png";
    tex_path[13] = ":/img/tex/arrow_p-15.png";
    tex_path[14] = ":/img/tex/arrow_p-30.png";
    tex_path[15] = ":/img/tex/arrow_p-45.png";
    tex_path[16] = ":/img/tex/arrow_p-60.png";
    tex_path[17] = ":/img/tex/arrow_p-75.png";
    tex_path[18] = ":/img/tex/arrow_p-90.png";
    tex_path[19] = ":/img/tex/arrow_p-105.png";
    tex_path[20] = ":/img/tex/arrow_p-120.png";
    tex_path[21] = ":/img/tex/arrow_p-135.png";
    tex_path[22] = ":/img/tex/arrow_p-150.png";
    tex_path[23] = ":/img/tex/arrow_p-165.png";

}

