#include "medium.h"
#include <cmath>

Medium::Medium(qreal x, qreal y, int dif, Player* pl)
{
    addPointToPath(x,y, pointList);

    player = pl;

    setPathTextures();

    if(rotate_angle == -1000)
        rotate_angle = 180;

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

void Medium::setPathTextures()
{
    tex_path[0] = ":/img/tex/EM0.png";
    tex_path[1] = ":/img/tex/EM15.png";
    tex_path[2] = ":/img/tex/EM30.png";
    tex_path[3] = ":/img/tex/EM45.png";
    tex_path[4] = ":/img/tex/EM60.png";
    tex_path[5] = ":/img/tex/EM75.png";
    tex_path[6] = ":/img/tex/EM90.png";
    tex_path[7] = ":/img/tex/EM105.png";
    tex_path[8] = ":/img/tex/EM120.png";
    tex_path[9] = ":/img/tex/EM135.png";
    tex_path[10] = ":/img/tex/EM150.png";
    tex_path[11] = ":/img/tex/EM165.png";
    tex_path[12] = ":/img/tex/EM180.png";
    tex_path[13] = ":/img/tex/EM-15.png";
    tex_path[14] = ":/img/tex/EM-30.png";
    tex_path[15] = ":/img/tex/EM-45.png";
    tex_path[16] = ":/img/tex/EM-60.png";
    tex_path[17] = ":/img/tex/EM-75.png";
    tex_path[18] = ":/img/tex/EM-90.png";
    tex_path[19] = ":/img/tex/EM-105.png";
    tex_path[20] = ":/img/tex/EM-120.png";
    tex_path[21] = ":/img/tex/EM-135.png";
    tex_path[22] = ":/img/tex/EM-150.png";
    tex_path[23] = ":/img/tex/EM-165.png";
}


