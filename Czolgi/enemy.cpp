/*
 *  File containing the enemy logic
 *  Author: Maks
 */

#include "enemy.h"
#include <cmath>

Enemy::Enemy()                                              //empty default constructor
{

}

void Enemy::holdPos()
{
    if(rotate_angle == -1000)
        rotate_angle = 180;
}

void Enemy::patrolPathHorizontaly(qreal end)
{
    if(!is_rotating)
    {
        if(reverso)
        {
            if(rotate_angle < 0)
                rotate_angle = rotate_angle +15;
            else if (rotate_angle > 0)
                rotate_angle = rotate_angle -15;
        }

        else
        {
            if(rotate_angle > 180)
                rotate_angle = rotate_angle -15;
            else if(rotate_angle < 180)
                rotate_angle = rotate_angle +15;
        }
    }

    if(x() >= end)                                          //check if the paths end
    {
        is_rotating = true;

        if(rotate_angle != 180)
        {
            rotate_angle = rotate_angle + 15;
        }
        else
        {
            reverso = true;                                     //set flag
            is_rotating = false;                                //set the flag
        }
    }

    if((x()-speed) < initx)                                 //check if start of the path
    {
        is_rotating = true;
        if(rotate_angle != 0)
        {
            rotate_angle = rotate_angle - 15;
        }
        else
        {
            reverso = false;                                     //set flag
            is_rotating = false;                                 //reset flag
        }
    }

    if(!reverso && !is_rotating)                            //determine the direction of movement
        Tank::move(speed,0);                                //move tank to the next point

    else if(reverso && !is_rotating)
        Tank::move(-speed,0);
}

void Enemy::patrolPathVerticaly(qreal end)
{
    if(!is_rotating)
    {
        if(reverso)
        {
            if(rotate_angle > -90 && rotate_angle <= 90)
                rotate_angle = rotate_angle -15;

            else if(rotate_angle < -90 || rotate_angle > 90)
            {
                rotate_angle = rotate_angle +15;
                if(rotate_angle >= 180)
                    rotate_angle = -165;
            }
        }

        else
        {
            if(rotate_angle > 90 || rotate_angle <= -90)
            {
                rotate_angle = rotate_angle -15;
                if(rotate_angle <= -165)
                    rotate_angle = 180;
            }
            else if(rotate_angle < 90 && rotate_angle > -90)
                rotate_angle = rotate_angle +15;
        }
    }

    if(y() >= end)                                          //check if the paths end
    {
        is_rotating = true;

        if(rotate_angle != (-90))
        {
            if(rotate_angle > -90 && rotate_angle <= 90)
                rotate_angle = rotate_angle - 15;
            else if(rotate_angle < -90 || rotate_angle > 90)
            {
                rotate_angle = rotate_angle +15;
                if(rotate_angle > 180)
                    rotate_angle = -165;
            }
        }
        else
        {
            reverso = true;                                     //set flag
            is_rotating = false;
        }
    }

    if((y()-speed) < inity)                                     //check if start of the path
    {
        is_rotating = true;
        if(rotate_angle != 90)
        {
            if(rotate_angle < 90 && rotate_angle >= -90)
                rotate_angle = rotate_angle + 15;
            else if(rotate_angle > 90 || rotate_angle < -90)
            {
                rotate_angle = rotate_angle -15;
                if(rotate_angle < -165)
                    rotate_angle = 180;
            }
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

void Enemy::followPlayer()
{
    qreal radian_angle = rotate_angle*M_PI/180;

    bool is_in_pos = false;

    if(abs(x()-player_lastx)<100 && abs(y()-player_lasty)<100)
    {
        is_in_pos = true;
    }

    if(!is_in_pos)
    {
        Tank::move(speed*cos(radian_angle), speed*sin(radian_angle));
    }

    if(!watchdog->isActive() && is_in_pos && !timer_was_set)
    {
        connect(watchdog,SIGNAL(timeout()),this,SLOT(comeBack()));
        watchdog->start(1000);
        timer_was_set = true;
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

        timer_was_set = false;

        aim(angle);
        shot(angle);
    }

    else
    {
        if(!was_spotted)
        {
            lastPosx = x();
            lastPosy = y();
        }

        if(was_spotted && !(command== GUARD || command==VERT || command==HORIZON))
            followPlayer();

        switch(command)
        {
            case VERT:
                patrolPathVerticaly(inity+300);
            break;

            case HORIZON:
                patrolPathHorizontaly(initx+300);
            break;

            case GUARD:
                holdPos();
            break;

            default:
            break;
        }
    }
}

void Enemy::comeBack()
{
    watchdog->stop();
    watchdog->start(50);

    qreal dx = x()-lastPosx;
    qreal dy = y()-lastPosy;

    float angle = atan2(dy,dx)*180/M_PI;

    if(angle <= 0)
        angle = angle + 180;
    else
        angle = angle - 180;

    if(abs(angle - rotate_angle) > 10)
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
            was_spotted = false;
            watchdog->start(1000);
            watchdog->stop();
            watchdog->disconnect(watchdog,SIGNAL(timeout()),this,SLOT(comeBack()));
            timer_was_set = false;
            return;
        }
        else
        {
            Tank::move(speed*cos(angle*M_PI/180), speed*sin(angle*M_PI/180));
        }
    }
}


