#include "enemy.h"
#include <cmath>

Enemy::Enemy()
{
}

void Enemy::patrolPathHorizontaly(qreal end)
{
    if(x() >= end)
    {
        reverso = true;
    }

    if((x()-speed)<= initx)
    {
        reverso = false;
    }

    if(!reverso)
        Tank::move(speed,0);

    else
        Tank::move(-speed,0);
}

void Enemy::patrolPathVerticaly(qreal end)
{
    if(y() >= end)
    {
        reverso = true;
    }

    if((y()-speed)<= inity)
    {
        reverso = false;
    }

    if(!reverso)
        Tank::move(0,speed);

    else
        Tank::move(0,-speed);
}

bool Enemy::check()
{
    int lenght = sqrt(pow(player->x() - this->x(),2)+pow(player->y() - this->y(),2));

    if(lenght >= view_range)
        return false;
    else
        return true;
}

void Enemy::setCommand(char comm)
{
    command = comm;
}


