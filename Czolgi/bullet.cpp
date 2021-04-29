#include "bullet.h"
#include <QGraphicsScene>
#include <QDebug>

Bullet::Bullet()
{
    this->setPixmap(QPixmap(":/img/tex/tex_bullet_01.png"));

    QTimer * timer = new QTimer();
    connect(timer, SIGNAL(timeout()),this,SLOT(move()));
    timer->start(10);
}

void Bullet::move()
{
    setPos(x()+speed, y());

    if(pos().x() > scene()->width() )
    {
        scene()->removeItem(this);
        delete this;
        qDebug() << "Pocisk skasowano";
    }

}
