#include "bullet.h"
#include <QGraphicsScene>
#include <QDebug>
#include <QList>
#include "enemy.h"

Bullet::Bullet()
{
    this->setPixmap(QPixmap(":/img/tex/tex_bullet_01.png"));

    QTimer * timer = new QTimer();
    connect(timer, SIGNAL(timeout()),this,SLOT(move()));
    timer->start(10);
}

void Bullet::move()
{

    QList<QGraphicsItem*> colliding_items = collidingItems();

    for (int i = 0, n = colliding_items.size(); i < n; i++)
    {
        if(typeid (*(colliding_items[i])) == typeid (Enemy))
        {
            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);

            delete colliding_items[i];
            delete this;
            return;
        }
    }

    setPos(x()+speed, y());

    if(pos().x() > scene()->width() )
    {
        scene()->removeItem(this);
        delete this;
        qDebug() << "Pocisk skasowano";
    }

}
