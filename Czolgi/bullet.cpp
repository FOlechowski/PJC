/*
 *  File containing the bullet implementation and logic
 *  Author: Maks
 */

#include "bullet.h"
#include <QGraphicsScene>
#include <QRandomGenerator>
#include <QDebug>
#include <QList>

#include "medium.h"
#include "destroyer.h"
#include "boss.h"
#include "heavy.h"
#include "light.h"
#include "obstacles.h"

#include "cmath"
#include "ctime"

Bullet::Bullet(float ang, Tank* tank)
{
    creator = tank;                                                     //save the pointer of the object that created bullet
    angle = ang;                                                        //set the value of the vector movement angle

    qreal deg_angle = (angle*180)/M_PI;                                 //calculate angle in degrees

    this->setPixmap(QPixmap(":/img/tex/tex_bullet_01.png"));            //set the texture for the bullet
    this->setTransformOriginPoint(20,5);                                //set the rotating point at the middle of the Pixmap
    this->setRotation(deg_angle);                                       //rotate the texture to be parallel to the movement vector

    QTimer * timer = new QTimer(this);                                  //start timer for it
    connect(timer, SIGNAL(timeout()),this,SLOT(moveBullet()));          //connect to the slot that will emitate the smooth movement
    timer->start(10);                                                   //start timer
}

Bullet::Bullet()
{
    ;
}

void Bullet::moveBullet()
{
    bool is_something_hitted = bulletIsCollidig();                                                                  //check if something was hitted

    if(!is_something_hitted)
    {
        setPos(x()+speed*cos(angle), y()+speed*sin(angle));                                                         //set position depending on the angle between the player and enemy

        if(pos().x() > scene()->width() || pos().x()<0 || pos().y() > scene()->height() || pos().y() < 0 )          //if bullet is out of the scene
        {
            scene()->removeItem(this);                                                                              //remove it from the scene and memory
            delete this;
        }
    }
}

bool Bullet::checkIfEnemy(QGraphicsItem *colliding_item)                                                            //check if typeid matches the enemies id
{
    if(typeid(*(colliding_item)) == typeid(Medium))
        return true;
    if(typeid(*(colliding_item)) == typeid(Destroyer))
        return true;
    if(typeid(*(colliding_item)) == typeid(Heavy))
        return true;
    if(typeid(*(colliding_item)) == typeid(Light))
        return true;
    if(typeid(*(colliding_item)) == typeid(Boss))
        return true;
    else
        return false;
}

bool Bullet::bulletIsCollidig()
{
    QList<QGraphicsItem*> colliding_items = collidingItems();                                               //create Qlist of colliding items

    for (int i = 0, n = colliding_items.size(); i < n; i++)                                                 //check the whole list
    {

        if(colliding_items[i] != creator && typeid(*(colliding_items[i])) != typeid(QGraphicsRectItem))
        {
            bool enemy = checkIfEnemy(colliding_items[i]);                                                      //check if enemy

            if((enemy || typeid (*(colliding_items[i])) == typeid (Player)))                                    //if enemy and the bullet didn't hit the creators
            {
                hitted = dynamic_cast<Tank*>(colliding_items[i]);                                               //safe pointer to the hitted element as Tank

                int hp = hitted->getHP();
                float armor = hitted->getArmor();
                int dmg = creator->getDMG();

                bool is_bouncing = false;//bounce();                                                                    //check if bullet has been bounced

                if(!is_bouncing)                                                                                //calculate damage
                {
                    hp = hp - (dmg - (armor*dmg));                                                              //calculate damage
                    hitted->setHP(hp);
                }

                if(typeid(*(colliding_items[i])) == typeid(Boss))
                {
                    Boss *P_Boss = dynamic_cast<Boss*>(colliding_items[i]);
                    P_Boss->getHelp(P_Boss->x()-200,P_Boss->y()-200);
                }

                if(hp <= 0 && enemy)                                                                             //if hp is over
                {
                    scene()->removeItem(hitted);                                                                //remove bullet and hited item
                    scene()->removeItem(this);

                    delete colliding_items[i];
                    delete this;
                    return true;                                                                                //end the function
                }

                else if(hp <=0 && !enemy)
                {
                    hitted->setHP(0);
                }

                scene()->removeItem(this);                                                                     //remove only bullet if hp is not over
                delete this;
                return true;                                                                                   //end the function
            }

            if(typeid (*(colliding_items[i]))!=typeid(Water) && typeid(*(colliding_items[i]))!=typeid(Bridge) && typeid(*(colliding_items[i]))!=typeid(QGraphicsTextItem))
            {
                scene()->removeItem(this);
                delete this;
                return true;
            }
        }
    }
    return false;
}

bool Bullet::bounce()
{
//    qreal angle_to_normal = abs(180-abs(hitted_angle - bullet_angle));                                      //calculate the angle

//    if(angle_to_normal>90)                                                                                  //check if it is in range 0-90
//        angle_to_normal = 180-angle_to_normal;

    quint32 chance = QRandomGenerator::global()->bounded(1,10);        //-(armor*10)+penetration/(angle_to_normal+1); //generate the chance to bounce

    if(chance < 2)
    {
       return true;
    }

    return false;
}
