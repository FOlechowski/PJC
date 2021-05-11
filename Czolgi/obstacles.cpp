#include "obstacles.h"

Obstacles::Obstacles()
{

}

Bridge::Bridge()
{
    this->setPixmap(QPixmap(":/img/tex/tex_bridge_1.png"));
}

Rock::Rock()
{
    this->setPixmap(QPixmap(":/img/tex/rock.png"));
}

Water::Water()
{
    QPixmap wt_tex(QString(":/img/tex/tex_water_01.png"));
    this->setBrush(QBrush(wt_tex));
}
