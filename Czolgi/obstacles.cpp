#include "obstacles.h"

obstacles::obstacles()
{

}

bridge::bridge()
{
    this->setPixmap(QPixmap(":/img/tex/tex_bridge_1.png"));
}

rock::rock()
{
    this->setPixmap(QPixmap(":/img/tex/rock.png"));

}
water::water()
{
    QPixmap wt_tex(QString(":/img/tex/tex_water_01.png"));
    this->setBrush(QBrush(wt_tex));
}
