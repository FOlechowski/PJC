#include "bullet.h"
#include <QGraphicsScene>
#include <QDebug>
#include <QList>
#include "enemy.h"
#include "cmath"

Bullet::Bullet(float ang, Tank* tank)
{
    creator = tank;

    this->setPixmap(QPixmap(":/img/tex/tex_bullet_01.png"));    //set the texture for the bullet

    QTimer * timer = new QTimer();                              //start timer for it
    connect(timer, SIGNAL(timeout()),this,SLOT(move()));        //connect to the slot that will emitate the smooth movement
    timer->start(10);                                           //start timer

    angle = ang;
}

void Bullet::move()
{
    //add switch case for the multiple types of objects
    QList<QGraphicsItem*> colliding_items = collidingItems();

    for (int i = 0, n = colliding_items.size(); i < n; i++)
    {
        if(typeid (*(colliding_items[i])) == typeid (Enemy) && (colliding_items[i] != creator))
        {
            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);

            qDebug()<<colliding_items[i];

            delete colliding_items[i];
            delete this;
            return;
        }

        if(typeid (*(colliding_items[i])) == typeid (Player) && (colliding_items[i] != creator))
        {

            scene()->removeItem(this);

            qDebug()<<colliding_items[i];
            qDebug()<<"Trafiono gracza!!!";

            delete this;
            return;
        }
    }

    setPos(x()+speed*cos(angle), y()+speed*sin(angle));

    if(pos().x() > scene()->width() || pos().x()<0 || pos().y() > scene()->height() || pos().y() < 0 )                             //if bullet is out of the scene
    {
        scene()->removeItem(this);                                //remove it from the scene and memory
        delete this;
        qDebug() << "Pocisk skasowano";
    }

}
