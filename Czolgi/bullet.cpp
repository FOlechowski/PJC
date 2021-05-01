#include "bullet.h"
#include <QGraphicsScene>
#include <QDebug>
#include <QList>
#include "enemy.h"

Bullet::Bullet()
{
    this->setPixmap(QPixmap(":/img/tex/tex_bullet_01.png"));    //set the texture for the bullet

    QTimer * timer = new QTimer();                              //start timer for it
    connect(timer, SIGNAL(timeout()),this,SLOT(move()));        //connect to the slot that will emitate the smooth movement
    timer->start(10);                                           //start timer
}

void Bullet::move()
{
    //add switch case for the multiple types of objects
    QList<QGraphicsItem*> colliding_items = collidingItems();

    for (int i = 0, n = colliding_items.size(); i < n; i++)
    {
        if(typeid (*(colliding_items[i])) == typeid (Enemy))
        {
            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);

            qDebug()<<colliding_items[i];

            delete colliding_items[i];
            delete this;
            return;
        }

        if(typeid (*(colliding_items[i])) == typeid (Player))
        {

            scene()->removeItem(this);

            qDebug()<<colliding_items[i];
            qDebug()<<"Trafiono gracza!!!";

            delete this;
            return;
        }
    }

    setPos(x()+speed, y());

    if(pos().x() > scene()->width() )                             //if bullet is out of the scene
    {
        scene()->removeItem(this);                                //remove it from the scene and memory
        delete this;
        qDebug() << "Pocisk skasowano";
    }

}
