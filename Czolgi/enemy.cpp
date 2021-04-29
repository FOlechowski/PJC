#include "enemy.h"
#include <math.h>

Enemy::Enemy(qreal x, qreal y,  Player* pl)
{
    initx = x;
    inity = y;

    player = pl;

    this->setPixmap(QPixmap(":/img/tex/tex_enemy_shadow_fd.png"));
    QTimer * timer = new QTimer();
    connect(timer, SIGNAL(timeout()),this,SLOT(move()));
    timer->start(20);
}

void Enemy::patrol_path(qreal end)
{

    bool is_inrange = check();

    if(!is_inrange)
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
    else
    {
        hold_pos();
    }
}

void Enemy::hold_pos()
{

}

bool Enemy::check()
{
    int lenght = sqrt(pow(player->x() - this->x(),2)+pow(player->y() - this->y(),2));

    if(lenght >= vrange)
    {
        return false;
    }
    else
    {
        return true;
    }
}

void Enemy::set_command(char comm)
{
    command = comm;
}

void Enemy::move()
{
    patrol_path(500);
}

void Enemy::attack()
{

}
