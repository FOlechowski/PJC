/*
 *  File containing the enemy logic
 *  Author: Maks
 */

#include "enemy.h"
#include "obstacles.h"
#include <cmath>

Enemy::Enemy()                                              //empty default constructor
{
}

void Enemy::holdPos()
{
    if(rotate_angle == -1000)
        rotate_angle = 180;
}

bool Enemy::check()
{
    int lenght = sqrt(pow(player->x() - this->x(),2)+pow(player->y() - this->y(),2));      //calculate the lenght between enemy and player

    if(lenght >= view_range)                                                               //if player is not in enemy's range
        return false;
    else
        return true;
}

void Enemy::aim(float angle)
{
    qreal deg_angle = (angle*180)/M_PI;                                                     //tranform angle between player and enemy to degrees

    if(deg_angle >= 0)                                                                      //check if player is above or belove the enemy
    {
        if((deg_angle - rotate_angle) > 10)                                                 //check if rotation is needed
        {
            if((deg_angle - rotate_angle)>180)                                              //check which rotation direction is more optimal
                rotate_angle = rotate_angle - 15;                                           //rotate counterclockwise
            else
                rotate_angle = rotate_angle + 15;                                           //rotate clockwise

            if(rotate_angle < -165)                                                         //if border
                rotate_angle = 180;                                                         //set the maximum value

            is_rotating = true;                                                             //set the flag
            return;
        }
        else if((deg_angle - rotate_angle) < -10)
        {
            rotate_angle = rotate_angle -15;
            is_rotating = true;
            return;
        }

        else
        {
            is_rotating = false;                                                            //reset the flag
            return;
        }
    }

    else
    {
        if((rotate_angle - deg_angle) > 10)
        {
            if((rotate_angle - deg_angle)<180)
                rotate_angle = rotate_angle - 15;
            else
                rotate_angle = rotate_angle + 15;

            if(rotate_angle>180)
                rotate_angle = -165;

            is_rotating = true;                                                             //set the flag
            return;
        }
        else if((rotate_angle - deg_angle) < -10)
        {
            rotate_angle = rotate_angle +15;
            is_rotating = true;
            return;
        }

        else
        {
            is_rotating = false;                                                            //reset the flag
            return;
        }
    }
}

void Enemy::setCommand(char comm)
{
    command = comm;                                         //set command
}

void Enemy::followPlayer()
{
    qreal radian_angle = rotate_angle*M_PI/180;

    bool is_in_pos = false;

    if(abs(x()-player_lastx)<50 && abs(y()-player_lasty)<50)
    {
        is_in_pos = true;
        qDebug()<<"Dotarłem na miejsce gracza";
    }

    if(!is_in_pos && !come_back)
    {
        Tank::move(speed*cos(radian_angle), speed*sin(radian_angle));
        qDebug()<<"Jade za graczem";
    }

    if(!watchdog->isActive() && is_in_pos && !timer_was_set)
    {
        connect(watchdog,SIGNAL(timeout()),this,SLOT(comeBack()));
        watchdog->start(1000);
        timer_was_set = true;
    }
}

void Enemy::addStick()
{
    stick = new QGraphicsRectItem(this);
    stick->setRect(50,50,2,(view_range-120));
    stick->setTransformOriginPoint(50,50);
    stick->setVisible(true);
}

bool Enemy::obstacleInLine()
{
    QList<QGraphicsItem*> colliding_items = stick->collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; i++)
    {
        if(typeid(*(colliding_items[i])) != typeid(Water) && typeid(*(colliding_items[i])) != typeid(Bridge) && colliding_items[i] != this)
            return true;
    }

    return false;
}

void Enemy::avoidObstacle()
{
    QList<QGraphicsItem*> colliding_items = stick->collidingItems();

    for (int i = 0, n = colliding_items.size(); i < n; i++)
    {

    }
}

void Enemy::addPointToPath(int x, int y)
{
    QPoint point;
    point.setX(x);
    point.setY(y);

    pointList.append(point);
}

void Enemy::goTo()
{
    int next = pointer + 1;
    if(pointer == pointList.size()-1)
    {
       next = 0;
    }

    int dx = pointList[pointer].x()-pointList[next].x();
    int dy = pointList[pointer].y()-pointList[next].y();

    float angle = atan2(dy,dx);

    if(angle >= 0)
    {
        angle = angle - M_PI;
    }

    else
    {
        angle = angle + M_PI;
    }

    aim(angle);

    if(!is_rotating)
    {
        Tank::move(speed*cos(angle),speed*sin(angle));
        qDebug()<<"Jade normalnie";
        if(abs(pointList[next].x() - this->x())<30 && abs(pointList[next].y() - this->y())<30)
        {
            qDebug()<<"Jestem w punkcie kontrolnym";
            pointer = pointer+1;
            if(pointer >= pointList.size())
            {
                pointer = 0;
            }
        }
    }
}

void Enemy::move()
{
    setTexture(rotate_angle);

    bool is_inrange = check();

    if(is_inrange)
    {
        int dx = (player->x()-50) - (this->x()-50);
        int dy = (player->y()-50) - (this->y()-50);

        player_lastx = player->x();
        player_lasty = player->y();

        float angle = atan2(dy,dx);

        was_spotted = true;
        come_back = false;
        timer_was_set = false;

        watchdog->start(1000);
        watchdog->stop();
        watchdog->disconnect(watchdog,SIGNAL(timeout()),this,SLOT(comeBack()));

        aim(angle);
        bool obstacle_in_line = obstacleInLine();

        if(!obstacle_in_line)
            shot(angle);
    }

    else
    {
        if(!was_spotted)
        {
            lastPosx = x();
            lastPosy = y();
            lastAngle = rotate_angle;
        }

        if(was_spotted && !(command == GUARD))
            followPlayer();

        switch(command)
        {
            case PATROL:
                    if(!was_spotted)
                        goTo();
            break;

            case GUARD:
                holdPos();
            break;

            default:
            break;
        }
    }

    if(stick != NULL)
    {
        stick->setRotation(rotate_angle-90);
    }
}

void Enemy::comeBack()
{
    bool is_back = false;
    come_back = true;

    watchdog->stop();
    watchdog->start(50);

    qreal dx = x()-lastPosx;
    qreal dy = y()-lastPosy;

    float angle = atan2(dy,dx)*180/M_PI;

    if(angle <= 0)
        angle = angle + 180;
    else
        angle = angle - 180;

    if(abs(angle - rotate_angle) > 10 && !(abs(lastPosx-x()) < 40 && abs(lastPosy-y()) < 40))
    {
        is_rotating = true;

        if(rotate_angle < angle)
        {
            rotate_angle = rotate_angle + 15;
        }

        else if(rotate_angle > angle)
        {
            rotate_angle = rotate_angle -15;
        }
    }
    else
    {
        is_rotating = false;
    }

    if(!is_rotating)
    {
        if( abs(lastPosx-x()) < 20 && abs(lastPosy-y()) < 20)
        {
            if(rotate_angle != lastAngle)
            { 
                if(rotate_angle > lastAngle)
                {
                    rotate_angle = rotate_angle -15;
                    if(rotate_angle < -165)
                        rotate_angle = 180;
                }
                else
                {
                    rotate_angle = rotate_angle +15;
                    if(rotate_angle > 180)
                        rotate_angle = -165;
                }
            }
            else
            {
                is_back = true;
                come_back = false;
            }
        }

        else
        {
            Tank::move(speed*cos(angle*M_PI/180), speed*sin(angle*M_PI/180));
            qDebug()<<"Wracam na pozycje";
        }
    }

    if(is_back)
    {
        was_spotted = false;
        watchdog->start(1000);
        watchdog->stop();
        watchdog->disconnect(watchdog,SIGNAL(timeout()),this,SLOT(comeBack()));
        timer_was_set = false;
        return;
    }
}


