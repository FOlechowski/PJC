#include "map.h"

Map::Map(Player* player)
{
    this->setSceneRect(0, 0, ms_width, ms_height);

    bridge = new QGraphicsRectItem;

    bridge->setRect(this->width()/2-150,this->height()/2,400,80);
    QPixmap br_tex(QString(":/img/tex/tex_wood_bridge_01.png"));
    bridge->setBrush(QBrush(br_tex));

    water = new QGraphicsRectItem;
    water->setRect(this->width()/2, 0, 100,this->height());
    QPixmap wt_tex(QString(":/img/tex/tex_water_01.png"));
    water->setBrush(QBrush(wt_tex));

    ply = player;
    ply->setFlag(QGraphicsItem::ItemIsFocusable);
    ply->setFocus();
    ply->setPos(50, this->height()/2);

    Enemy *enemy = new Enemy(750,100, ply);
    enemy->setPos(enemy->initx, enemy->inity);

    Enemy *enemy2 = new Enemy(350,200, ply);
    enemy2->setPos(enemy2->initx, enemy2->inity);

    QPixmap bground_img(QString(":/img/tex/tex_sand_01.png"));

    this->setBackgroundBrush(QBrush(bground_img));

    this->addItem(water);
    this->addItem(bridge);
    this->addItem(enemy);
    this->addItem(enemy2);
    this->addItem(ply);

    qDebug() << "cus sie popsulo, ale troche dziala";
}

Map::~Map()
{
    delete bridge;
    delete water;
    delete wall1;
    delete wall2;
}


