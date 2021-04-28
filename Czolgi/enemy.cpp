#include "enemy.h"

Enemy::Enemy()
{
    this->setPixmap(QPixmap(":/img/tex/tex_enemy_shadow_fd.png"));
    QTimer * timer = new QTimer();
    connect(timer, SIGNAL(timeout()),this,SLOT(move()));
    timer->start(25);
}

void Enemy::patrol(qreal end)
{
    if(y() >= end)
    {
        reverso = true;
        this->setPixmap(QPixmap(":/img/tex/tex_enemy_shadow_bck.png"));
    }

    if((y()-speed)<= inity)
    {
        reverso = false;
        this->setPixmap(QPixmap(":/img/tex/tex_enemy_shadow_fd.png"));
    }

    if(!reverso)
        setPos(x(),y()+speed);

    else
        setPos(x(),y()-speed);

}

void Enemy::move()
{
    patrol(500);
}
