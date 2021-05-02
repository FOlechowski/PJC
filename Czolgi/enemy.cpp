#include "enemy.h"
#include <cmath>

Enemy::Enemy(qreal x, qreal y,  Player* pl)
{
    initx = x;
    inity = y;

    player = pl;

    this->setPixmap(QPixmap(":/img/tex/tex_enemy_shadow_fd.png"));
    QTimer * timer_move = new QTimer();
    connect(timer_move, SIGNAL(timeout()),this,SLOT(move()));
    connect(timer_reload, SIGNAL(timeout()),this,SLOT(reload()));
    timer_move->start(30);

    speed = 2;
    view_range = 300;

    hp = 200;
    armor = 0.5;
    dmg = 50;

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

        int dx = (player->x()-50) - (this->x()-50);
        int dy = (player->y()-50) - (this->y()-50);

        float angle = atan2(dy,dx);

        shot(angle);
    }
}

void Enemy::hold_pos()
{

}

bool Enemy::check()
{
    int lenght = sqrt(pow(player->x() - this->x(),2)+pow(player->y() - this->y(),2));

    if(lenght >= view_range)
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
