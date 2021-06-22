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

Decoration1::Decoration1()
{
     this->setPixmap(QPixmap(":/img/tex/decoration_1.png"));
}

Decoration2::Decoration2()
{
     this->setPixmap(QPixmap(":/img/tex/decoration_2.png"));
}


UTrack::UTrack()
{
    this->setPixmap(QPixmap(":/img/tex/track.png"));
    this->setScale(0.15);
}

UEngine::UEngine()
{
    this->setPixmap(QPixmap(":/img/tex/Engine.png"));
    this->setScale(0.1);
}

UArmor::UArmor()
{
    this->setPixmap(QPixmap(":/img/tex/Armor.png"));
    this->setScale(0.1);
}

UChest::UChest()
{
    this->setPixmap(QPixmap(":/img/tex/Chest.png"));
    this->setScale(0.15);
}

UHealth::UHealth()
{
    this->setPixmap((QPixmap(":/img/tex/Health.png")));
    this->setScale(0.05);
}

