/*
 *  File containing the bullet implementation and logic
 *  Author: Maks
 */

#include "bullet.h"
#include <QGraphicsScene>
#include <QDebug>
#include <QList>
#include "enemy.h"
#include "cmath"

Bullet::Bullet(float ang, Tank* tank)
{
    creator = tank;                                             //save the pointer of the object that created bullet
    angle = ang;                                                //set the value of the vector movement angle

    qreal deg_angle = (angle*180)/M_PI;                         //calculate angle in degrees

    this->setPixmap(QPixmap(":/img/tex/tex_bullet_01.png"));    //set the texture for the bullet
    this->setTransformOriginPoint(20,5);                        //set the rotating point at the middle of the Pixmap
    this->setRotation(deg_angle);                               //rotate the texture to be parallel to the movement vector

    QTimer * timer = new QTimer();                              //start timer for it
    connect(timer, SIGNAL(timeout()),this,SLOT(move()));        //connect to the slot that will emitate the smooth movement
    timer->start(10);                                           //start timer


}

void Bullet::move()
{

    QList<QGraphicsItem*> colliding_items = collidingItems();                                   //create Qlist of colliding items

    for (int i = 0, n = colliding_items.size(); i < n; i++)                                     //check the whole list
    {
        if(typeid (*(colliding_items[i])) == typeid (Enemy) && (colliding_items[i] != creator)) //if type id is matching and the bullet didn't hit the creators
        {
            hitted = dynamic_cast<Tank*>(colliding_items[i]);                                   //safe pointer to the hitted element

            hitted->hp = hitted->hp - creator->dmg * hitted->armor;                             //calculate damage

            if(!(hitted->hp))                                                                   //if hp is over
            {
                scene()->removeItem(hitted);                                                    //remove bullet and hited item
                scene()->removeItem(this);

                delete colliding_items[i];
                delete this;
                return;                                                                         //end the function
            }
             scene()->removeItem(this);                                                         //remove only bullet
             delete this;
             qDebug()<<hitted->hp;
             return;                                                                            //end the function
        }


        //add ability do decrease the player hp
        if(typeid (*(colliding_items[i])) == typeid (Player) && (colliding_items[i] != creator))    //same as above
        {

            scene()->removeItem(this);

            //qDebug()<<colliding_items[i];
            //qDebug()<<"Trafiono gracza!!!";

            delete this;
            return;
        }
    }

    setPos(x()+speed*cos(angle), y()+speed*sin(angle));                                                         //set position depending on the angle between the player and enemy

    if(pos().x() > scene()->width() || pos().x()<0 || pos().y() > scene()->height() || pos().y() < 0 )          //if bullet is out of the scene
    {
        scene()->removeItem(this);                                                                              //remove it from the scene and memory
        delete this;
    }

}
