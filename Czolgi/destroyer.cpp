#include "destroyer.h"
#include "cmath"

Destroyer::Destroyer(qreal x, qreal y, int dif, Player* pl)
{
    addPointToPath(x,y);

    player = pl;

    setPathTextures();

    QTimer * timer_move = new QTimer();
    connect(timer_move, SIGNAL(timeout()),this,SLOT(move()));
    connect(timer_reload, SIGNAL(timeout()),this,SLOT(reload()));
    timer_move->start(35);

    switch(dif)
    {
        case 0:
            speed = 2;
            view_range = 400;
            hp = 100;
            armor = 0.3;
            dmg = 100;
            reload_time = 6000;
            break;
        case 1:
            speed = 2;
            view_range = 500;
            hp = 350;
            armor = 0.35;
            dmg = 150;
            reload_time = 5000;
            break;
        case 2:
            speed = 2;
            view_range = 600;
            hp = 500;
            armor = 0.45;
            dmg = 200;
            reload_time = 4000;
            break;
    }
}

void Destroyer::setPathTextures()
{
    tex_path[0] = ":/img/tex/arrow_0.png";
    tex_path[1] = ":/img/tex/arrow_15.png";
    tex_path[2] = ":/img/tex/arrow_30.png";
    tex_path[3] = ":/img/tex/arrow_45.png";
    tex_path[4] = ":/img/tex/arrow_60.png";
    tex_path[5] = ":/img/tex/arrow_75.png";
    tex_path[6] = ":/img/tex/arrow_90.png";
    tex_path[7] = ":/img/tex/arrow_105.png";
    tex_path[8] = ":/img/tex/arrow_120.png";
    tex_path[9] = ":/img/tex/arrow_135.png";
    tex_path[10] = ":/img/tex/arrow_150.png";
    tex_path[11] = ":/img/tex/arrow_165.png";
    tex_path[12] = ":/img/tex/arrow_180.png";
    tex_path[13] = ":/img/tex/arrow_-15.png";
    tex_path[14] = ":/img/tex/arrow_-30.png";
    tex_path[15] = ":/img/tex/arrow_-45.png";
    tex_path[16] = ":/img/tex/arrow_-60.png";
    tex_path[17] = ":/img/tex/arrow_-75.png";
    tex_path[18] = ":/img/tex/arrow_-90.png";
    tex_path[19] = ":/img/tex/arrow_-105.png";
    tex_path[20] = ":/img/tex/arrow_-120.png";
    tex_path[21] = ":/img/tex/arrow_-135.png";
    tex_path[22] = ":/img/tex/arrow_-150.png";
    tex_path[23] = ":/img/tex/arrow_-165.png";
}

