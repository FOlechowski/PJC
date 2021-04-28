#include "map.h"

Map::Map(Player* player)
{
    this->setSceneRect(0, 0, ms_width, ms_height);

    bridge = new QGraphicsRectItem;

    bridge->setRect(this->width()/2-150,this->height()/2,400,80);
    QPixmap br_tex(QString(":/img/tex/tex_wood_bridge_01.png"));
    bridge->setBrush(QBrush(br_tex));

    wall1 = new QGraphicsRectItem;
    wall1->setRect(this->width()/2-150, this->height()/2-30, 400, 30);
    QPixmap w1_tex(QString(":/img/tex/tex_sand_01.png"));
    wall1->setBrush(QBrush(w1_tex));

    wall2 = new QGraphicsRectItem;
    wall2->setRect(this->width()/2-150, this->height()/2+80, 400, 30);
    wall2->setBrush(QBrush(w1_tex));

    water = new QGraphicsRectItem;
    water->setRect(this->width()/2, 0, 100,this->height());
    QPixmap wt_tex(QString(":/img/tex/tex_water_01.png"));
    water->setBrush(QBrush(wt_tex));

    Enemy *enemy = new Enemy();
    enemy->setPos(enemy->initx,enemy->inity);

    ply = player;
    ply->setFlag(QGraphicsItem::ItemIsFocusable);
    ply->setFocus();
    ply->setPos(50,this->height()/2);

    QPixmap bground_img(QString(":/img/tex/tex_sand_01.png"));

    this->setBackgroundBrush(QBrush(bground_img));

    this->addItem(water);
    this->addItem(bridge);
    this->addItem(wall1);
    this->addItem(player);
    this->addItem(wall2);
    this->addItem(enemy);

    qDebug() << "cus sie popsulo, ale troche dziala";
}

Map::~Map()
{
    delete bridge;
    delete water;
    delete wall1;
    delete wall2;
}


