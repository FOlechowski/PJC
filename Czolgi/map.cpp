#include "map.h"

Map::Map()
{
    map = new QGraphicsView(this);
    map->setFixedSize(QSize(mv_width, mv_height));

    map->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    map->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    this->setSceneRect(0, 0, ms_width, ms_height);

    bridge = new QGraphicsRectItem;

    bridge->setRect(this->width()/2-150,this->height()/2,400,80);
    //QPixmap br_tex(QString(":/img/img/stone_texture.png"));
    //bridge->setBrush(QBrush(br_tex));

    wall1 = new QGraphicsRectItem;
    wall1->setRect(this->width()/2-150, this->height()/2-30, 400, 30);
    //QPixmap w1_tex(QString(":/img/img/wall.png"));
    //wall1->setBrush(QBrush(w1_tex));

    wall2 = new QGraphicsRectItem;
    wall2->setRect(this->width()/2-150, this->height()/2+80, 400, 30);
    //wall2->setBrush(QBrush(w1_tex));

    water = new QGraphicsRectItem;
    water->setRect(this->width()/2, 0, 100,this->height());
    //QPixmap wt_tex(QString(":/img/img/water.png"));
    //water->setBrush(QBrush(wt_tex));

    player = new Player();
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    player->setPos(50,this->height()/2);

    //QPixmap bground_img(QString(":/img/img/grass_texture.png"));
    //bground_img = bground_img.scaled(mv_width, mv_height , Qt::IgnoreAspectRatio);      //scale background image to window size
    //this->setBackgroundBrush(QBrush(bground_img));

    this->addItem(water);
    this->addItem(bridge);
    this->addItem(wall1);
    this->addItem(player);
    this->addItem(wall2);

    map->setScene(this);

    map->show();

    qDebug() << "cus sie popsulo, ale troche dziala";
}

Map::~Map()
{
    delete map;
    delete player;
    delete bridge;
    delete water;
    delete wall1;
    delete wall2;
}


