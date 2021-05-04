/*
 *  File containing the enemy logic
 *  Author: Maks
 */

#include "enemy.h"
#include <cmath>

Enemy::Enemy()                                              //empty default constructor
{
}

void Enemy::patrolPathHorizontaly(qreal end)
{
    if(rotate_angle == -1000)
        rotate_angle = 0;

    if(x() >= end)                                          //check if the paths end
    {
        reverso = true;                                     //set the flag
    }

    if((x()-speed)<= initx)                                 //check if start of the path
    {
        reverso = false;                                    //reset the flag
    }

    if(!reverso)                                            //determine the direction of movement
        Tank::move(speed,0);                                //move tank to the next point

    else
        Tank::move(-speed,0);
}

void Enemy::patrolPathVerticaly(qreal end)
{
    if(rotate_angle == -1000)
        rotate_angle = 90;

    if(!is_rotating && (rotate_angle!=90 && rotate_angle!=-90))
    {
        if(reverso)
        {
            if(rotate_angle < -90)
                rotate_angle = rotate_angle +15;
            else
                rotate_angle = rotate_angle -15;
        }

        else
        {
            if(rotate_angle > 90)
                rotate_angle = rotate_angle -15;
            else
                rotate_angle = rotate_angle +15;
        }
    }

    if(y() >= end)                                          //check if the paths end
    {
        is_rotating = true;

        if(rotate_angle != (-90))
        {
            rotate_angle = rotate_angle - 15;
        }
        else
        {
            reverso = true;                                     //set flag
            is_rotating = false;
        }
    }

    if((y()-speed)<= inity)                                     //check if start of the path
    {
        is_rotating = true;
        if(rotate_angle != 90)
        {
            rotate_angle = rotate_angle + 15;
        }
        else
        {
            reverso = false;                                     //set flag
            is_rotating = false;                                 //reset flag
        }
    }

    if(!reverso && !is_rotating)                                //determine the direction of movement
        Tank::move(0,speed);                                    //move tank to the next point

    else if(reverso && !is_rotating)
        Tank::move(0,-speed);
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
        if((deg_angle - rotate_angle) > 15)                                                 //check if rotation is needed
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
        else if((deg_angle - rotate_angle) < -15)
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
        if((rotate_angle - deg_angle) > 15)
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
        else if((rotate_angle - deg_angle) < -15)
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
    command = comm;                                                                         //set command
}


