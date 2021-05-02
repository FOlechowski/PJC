#include "medium.h"
#include <cmath>

Medium::Medium(qreal x, qreal y, int dif, Player* pl)
{
    initx = x;
    inity = y;

    player = pl;

    this->setPixmap(QPixmap(":/img/tex/tex_enemy_shadow_fd.png"));
    QTimer * timer_move = new QTimer();
    connect(timer_move, SIGNAL(timeout()),this,SLOT(move()));
    connect(timer_reload, SIGNAL(timeout()),this,SLOT(reload()));
    timer_move->start(35);

    switch(dif)
    {
        case 0:
            speed = 2;
            view_range = 250;
            hp = 150;
            armor = 0.35;
            dmg = 20;
            reload_time = 5000;
            break;
        case 1:
            speed = 2;
            view_range = 350;
            hp = 350;
            armor = 0.45;
            dmg = 50;
            reload_time = 4000;
            break;
        case 2:
            speed = 2;
            view_range = 400;
            hp = 500;
            armor = 0.5;
            dmg = 80;
            reload_time = 3000;
            break;
    }
}

void Medium::move()
{
    bool is_inrange = check();

    if(is_inrange)
    {
        int dx = (player->x()-50) - (this->x()-50);
        int dy = (player->y()-50) - (this->y()-50);

        float angle = atan2(dy,dx);

        shot(angle);
    }
    else
    {
        switch(command)
        {
            case VERT:
                Enemy::patrolPathVerticaly(inity+300);
                if(reverso)
                    this->setPixmap(QPixmap(":/img/tex/tex_enemy_shadow_bck.png"));
                else
                    this->setPixmap(QPixmap(":/img/tex/tex_enemy_shadow_fd.png"));
            break;

            case HORIZON:
                Enemy::patrolPathHorizontaly(initx+300);
            break;

            default:
            break;
        }

    }
}

