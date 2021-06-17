#include "player.h"
#include <cmath>
#include "bullet.h"
#include "explosivebullet.h"


Player::Player()
{
    this->setPixmap(QPixmap(":/img/tex/p0.png"));
    this->setTransformOriginPoint(50,50);
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

void Player::setPointerToView(QGraphicsView *view)
{
    this->view = view;
}

void Player::moveForward(qreal m_distance, double m_angle)
{

    Tank::move(cos(m_angle*M_PI/180)*m_distance,-sin(m_angle*M_PI/180)*m_distance);


}

void Player::moveBackward(qreal m_distance, double m_angle)
{

    Tank::move(-cos(m_angle*M_PI/180)*m_distance/2,sin(m_angle*M_PI/180)*m_distance/2);


}

void Player::turnLeft(double &m_angle)
{

    m_angle += 2.5;
    //this->setRotation(-m_angle);
    if(m_angle>180)
    {
        m_angle=-177.5;
    }


}

void Player::turnRight(double &m_angle)
{

    m_angle -= 2.5;
    //this->setRotation(-m_angle);
    if(m_angle<-180)
    {
        m_angle=177.5;
    }



}

bool Player::checkCol()
{
    QList<QGraphicsItem*> colliding_items = collidingItems();
    //qDebug()<<typeid(Bridge);
    bool isonbridge,isonwater,stick = false;

    for (int i = 0, n = colliding_items.size(); i < n; i++){

        if(typeid((*colliding_items[i])) == typeid(Bridge)){
            isonbridge = true;
        }else{
            isonbridge = false;
        }
        if (typeid((*colliding_items[i])) == typeid(Water))
        {
            isonwater = true;
        }else{
            isonwater = false;
        }
        if (typeid((*colliding_items[i])) == typeid(QGraphicsRectItem)){
            stick = true;
            //qDebug()<<"patykuje";
        }else{
            stick = false;
        }

    }

    if(colliding_items.size()==0||(isonbridge&&!isonwater)||(stick&&colliding_items.size()==1)||(stick&&!isonwater&&colliding_items.size()==2)||(stick&&!isonwater&&isonbridge&&colliding_items.size()==3)){
        return true;
    }else if(colliding_items.size()!=0){
        return false;
    }

}
void Player::movePlayer()
{
    if (checkCol()&&!(keyA&&keyD)){

        if(view!=nullptr){
        view->centerOn(this);
        view->show();
        }

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
            moveBackward(5*speed,rotate_angle);
            if (checkCol()){
            front_hit=false;
            }
        }
        if(back_hit&&keyW){
            moveForward(3*speed,rotate_angle);
            if (checkCol()){
            back_hit=false;
            }
        }
        if(right_hit&&keyA){
            turnLeft(rotate_angle);
            if (checkCol()){
            right_hit=false;
            }
        }
        if(left_hit&&keyD){
            turnRight(rotate_angle);
            if (checkCol()){
            left_hit=false;
            }
        }

    }

    if(keySpace)
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



    //if(!rotate_angle%15){
    Tank::setTexture(-rotate_angle);
    //qDebug()<<-rotate_angle;
    //}

    if((this->pos()).y()>=450){

    }
}

void Player::addPlayerTextures(){
    tex_path[0] = ":/img/tex/p0.png";
    tex_path[1] = ":/img/tex/p15.png";
    tex_path[2] = ":/img/tex/p30.png";
    tex_path[3] = ":/img/tex/p45.png";
    tex_path[4] = ":/img/tex/p60.png";
    tex_path[5] = ":/img/tex/p75.png";
    tex_path[6] = ":/img/tex/p90.png";
    tex_path[7] = ":/img/tex/p105.png";
    tex_path[8] = ":/img/tex/p120.png";
    tex_path[9] = ":/img/tex/p135.png";
    tex_path[10] = ":/img/tex/p150.png";
    tex_path[11] = ":/img/tex/p165.png";
    tex_path[12] = ":/img/tex/p180.png";
    tex_path[13] = ":/img/tex/p-15.png";
    tex_path[14] = ":/img/tex/p-30.png";
    tex_path[15] = ":/img/tex/p-45.png";
    tex_path[16] = ":/img/tex/p-60.png";
    tex_path[17] = ":/img/tex/p-75.png";
    tex_path[18] = ":/img/tex/p-90.png";
    tex_path[19] = ":/img/tex/p-105.png";
    tex_path[20] = ":/img/tex/p-120.png";
    tex_path[21] = ":/img/tex/p-135.png";
    tex_path[22] = ":/img/tex/p-150.png";
    tex_path[23] = ":/img/tex/p-165.png";

}

