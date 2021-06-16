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
    goTo(pr_pointer,pursuitList);
}

void Enemy::addStick()
{
    stick = new QGraphicsRectItem(this);
    stick->setRect(25,80,50,(view_range));
    stick->setTransformOriginPoint(50,50);
    stick->setVisible(false);

    txt = new QGraphicsTextItem(this);
    txt -> setDefaultTextColor(Qt::red);
    txt -> setFont(QFont("calibri", 24));
    txt -> setPos(20, -35);
}

bool Enemy::obstacleInLine()
{
    QList<QGraphicsItem*> colliding_items = stick->collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; i++)
    {
        if(typeid(*(colliding_items[i])) != typeid(Water) && typeid(*(colliding_items[i])) != typeid(Bridge) && colliding_items[i] != this && typeid(*(colliding_items[i])) != typeid(Player))
            return true;
    }
    return false;
}

bool Enemy::avoidObstacle()
{
    bool obstacle_in_view = false;
    if(!is_rotating)
        obstacle_in_view = obstacleInLine();
    if(obstacle_in_view)
    {
        return false;
    }
    return true;
}

void Enemy::addPointToPath(int x, int y, QList<QPoint> &list)
{
    QPoint point;
    point.setX(x);
    point.setY(y);

    list.append(point);
}

void Enemy::goTo(int &pointer, QList<QPoint> &list)
{
    int next = pointer + 1;
    if(pointer == list.size()-1)
    {
       next = 0;
    }

    int dx = list[pointer].x()-list[next].x();
    int dy = list[pointer].y()-list[next].y();

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
        if(abs(list[next].x() - this->x())<30 && abs(list[next].y() - this->y())<30)
        {
            pointer = pointer+1;
            if(pointer >= list.size())
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
        aim(angle);


        bool obstacle_in_line = obstacleInLine();

        if(!obstacle_in_line && !is_rotating)
        {
            was_spotted = true;
            shot(angle);
            if(!pursuitList.size())
            {
                addPointToPath(this->x(),this->y(),pursuitList);
                addPointToPath(player_lastx,player_lasty,pursuitList);
            }

            else
            {
                pursuitList[pursuitList.size()-1].rx() = player_lastx;
                pursuitList[pursuitList.size()-1].ry() = player_lasty;
                pursuitList[0].rx() = this->x();
                pursuitList[0].ry() = this->y();
            }

        }
    }

    else
    {
        if(!was_spotted)
        {
            lastPosx = x();
            lastPosy = y();
        }

        if(was_spotted && !(command == GUARD))
            followPlayer();

        switch(command)
        {
            case PATROL:
                    if(!was_spotted)
                        goTo(pointer,pointList);
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
        QString hp = QString::number(this->hp);
        txt -> setPlainText(hp);
    }
}


