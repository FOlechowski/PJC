#include "map.h"
#include "medium.h"
#include "destroyer.h"

Map::Map(Player* player, int diff)
{
    difficult = diff;

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
    ply->setPos(50, 50);

    Medium *enemy = new Medium(750,100, difficult, ply);
    enemy->setPos(enemy->initx, enemy->inity);
    enemy->setCommand(VERT);

    Medium *enemy2 = new Medium(350,200, difficult, ply);
    enemy2->setPos(enemy2->initx, enemy2->inity);
    enemy2->setCommand(VERT);

    Destroyer *enemy3= new Destroyer(50,550, difficult, ply);
    enemy3->setPos(enemy3->initx, enemy3->inity);
    enemy3->setCommand(GUARD);

    QPixmap bground_img(QString(":/img/tex/tex_sand_01.png"));

    this->setBackgroundBrush(QBrush(bground_img));

    this->addItem(water);
    this->addItem(bridge);
    this->addItem(enemy);
    this->addItem(enemy2);
    this->addItem(enemy3);
    this->addItem(ply);

    qDebug() << difficult;
}

Map::~Map()
{
    delete bridge;
    delete water;
    delete wall1;
    delete wall2;
}




