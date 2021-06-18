#include "boss.h"

Boss::Boss(qreal x, qreal y, int dif, Player* pl)
{
    addPointToPath(x,y,pointList);
    player = pl;

    setPathTextures();

    QTimer * timer_move = new QTimer();
    connect(timer_move, SIGNAL(timeout()),this,SLOT(move()));
    connect(timer_reload, SIGNAL(timeout()),this,SLOT(reload()));
    timer_move->start(35);

    switch(dif)
    {
        case 0:
            speed = 3;
            view_range = 500;
            hp = 1000;
            armor = 0.8;
            dmg = 100;
            reload_time = 4000;
            break;
        case 1:
            speed = 4;
            view_range = 500;
            hp = 1200;
            armor = 0.85;
            dmg = 150;
            reload_time = 3500;
            break;
        case 2:
            speed = 4;
            view_range = 550;
            hp = 2500;
            armor = 0.9;
            dmg = 180;
            reload_time = 2000;
            break;
    }

    initial_hp = this->hp;
    game_dif = dif;
}

Boss::~Boss()
{
    qDebug()<<"Robię destruktor od Bossa";
}

void Boss::setPathTextures()
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

void Boss::getHelp(qreal x, qreal y)
{
    if(this->hp < initial_hp && m_counter != 0)
    {
        Medium *medium = new Medium(x,y,game_dif,player);
        medium->addStick();
        medium->setPos(x,y);

        if(m_counter == 2)
        {
            medium->addPointToPath(crd[0], crd[1], medium->pointList);
        }
        else
        {
            medium->addPointToPath(crd[2], crd[3], medium->pointList);
        }

        medium->setCommand(PATROL);
        m_counter --;
        scene()->addItem(medium);
        qDebug()<<medium->pointList;
    }
}
