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

    QTimer * player_timer = new QTimer();                              //start timer for it
    connect(player_timer, SIGNAL(timeout()),this,SLOT(movePlayer()));        //connect to the slot that will emitate the smooth movement
    player_timer->start(40);

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

    Tank::move(cos(m_angle*M_PI/180)*m_distance,-sin(m_angle*M_PI/180)*m_distance);
}

void Player::moveBackward(qreal m_distance, int m_angle)
{

    Tank::move(-cos(m_angle*M_PI/180)*m_distance/2,sin(m_angle*M_PI/180)*m_distance/2);
}

void Player::turnLeft(int &m_angle)
{

    m_angle += 5;
    if(m_angle>180)
    {
        m_angle=-175;
    }
}

void Player::turnRight(int &m_angle)
{

    m_angle -= 5;
    if(m_angle<-180)
    {
        m_angle=175;
    }
}


void Player::keyPressEvent(QKeyEvent *event)
{

    //qDebug()<<colliding_items;
    //grabKeyboard();
    if(event->key() == Qt::Key_A)
    {
        keyA = true;
        //qDebug()<<"pressed A";
    }

    if(event->key() == Qt::Key_D)
    {
        keyD = true;
        //qDebug()<<"pressed D";
    }

    if(event->key() == Qt::Key_W)
    {
        keyW = true;
        //qDebug()<<"pressed W";
    }

    if(event->key() == Qt::Key_S)
    {
        keyS = true;
        //qDebug()<<"pressed S";
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
<<<<<<< HEAD
    qDebug()<<this->pos();
    //qDebug()<<rotate_angle;
=======
    //qDebug()<<this->pos();
    //qDebug()<<rotate_angle;

>>>>>>> dc2c38c7e66095620ec8d044f32c9ac9fbf0952f


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

void Player::movePlayer()
{
    QList<QGraphicsItem*> colliding_items = collidingItems();

    if (colliding_items.size()==0){
        if(keyA){
            if(keyW){
                turnLeft(rotate_angle);
                moveForward(speed,rotate_angle);

            }else if(keyS){
                turnLeft(rotate_angle);
                moveBackward(speed,rotate_angle);

            }else{
            turnLeft(rotate_angle);
            turnLeft(rotate_angle);
            }
        }

        if(keyD){
            if(keyW){
                turnRight(rotate_angle);
                moveForward(speed,rotate_angle);

            }else if(keyS){
                turnRight(rotate_angle);
                moveBackward(speed,rotate_angle);

            }else{
            turnRight(rotate_angle);
            turnRight(rotate_angle);
            }
        }

        if(keyW){
            if(keyA){
                moveForward(speed,rotate_angle);
                turnLeft(rotate_angle);


            }else if(keyD){
                moveForward(speed,rotate_angle);

                turnRight(rotate_angle);

            }else{
            moveForward(2*speed,rotate_angle);
            }
        }

        if(keyS){
            if(keyA){
                moveBackward(speed,rotate_angle);
                turnLeft(rotate_angle);
            }else if(keyD){
                moveBackward(speed,rotate_angle);
                turnRight(rotate_angle);
            }else{
            moveBackward(2*speed,rotate_angle);
            }
        }
    }else{
        if(keyW&&!front_hit&&!back_hit&&!right_hit&&!left_hit){
            front_hit = true;
        }else if(keyS&&!front_hit&&!back_hit&&!right_hit&&!left_hit){
            back_hit = true;
        }else if(keyA&&!front_hit&&!back_hit&&!right_hit&&!left_hit){
            left_hit = true;
        }else if(keyD&&!front_hit&&!back_hit&&!right_hit&&!left_hit){
            right_hit = true;
        }

        if(front_hit&&keyS){
            moveBackward(4*speed,rotate_angle);
            front_hit=false;

        }
        if(back_hit&&keyW){
            moveForward(2*speed,rotate_angle);
            back_hit=false;
        }
        if(right_hit&&keyA){
            turnLeft(rotate_angle);
            right_hit=false;
        }
        if(left_hit&&keyD){
            turnRight(rotate_angle);
            left_hit=false;
        }

    }

    Tank::setTexture(-rotate_angle);
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

