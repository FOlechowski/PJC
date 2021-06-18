#include "map.h"
#include "medium.h"
#include "destroyer.h"
#include "light.h"
#include "boss.h"

Map::Map(Player* player, int diff)
{
    difficult = diff;
    level = 1;

    this->setSceneRect(-50, 0, ms_width, ms_height);

//    Bridge* bridge_1 = new Bridge;
//    bridge_1->setPos(525,150);

//    Water* water_1 = new Water;
//    Water* water_2 = new Water;
//    water_1->setRect(this->width()/2, 0, 100,150);
//    water_2->setRect(this->width()/2, 270, 100,this->width()-270);

    //qDebug()<<bridge->data(bridge->type());
//    for(int i=0; i<450; i=i+50)
//    {
//        Rock* rock_1 = new Rock;
//        rock_1->setPos(400,100+i);
//        this->addItem(rock_1);
//    }

//    Rock* rock_1 = new Rock;
//    rock_1->setPos(750,100);
//    this->addItem(rock_1);

//    Rock* rock_2 = new Rock;
//    rock_2->setPos(750,200);
//    this->addItem(rock_2);

    ply = player;
    ply->setFlag(QGraphicsItem::ItemIsFocusable);
    ply->setFocus();
    ply->setPos(0, 0);
    ply->setPointerToMap(this);

    Boss *enemy = new Boss(500,200, difficult, ply);
    enemy->setPos(enemy->pointList[0].x(), enemy->pointList[0].y());
    enemy->setCommand(PATROL);
    this->addItem(enemy);
    enemy->addStick();
    enemy->addPointToPath(500,400, enemy->pointList);

//    Boss *boss = new Boss(900,500,difficult,ply);
//    boss->setPos(boss->pointList[0].x(), boss->pointList[0].y());
//    boss->setCommand(GUARD);
//    this->addItem(boss);
//    boss->addStick();

//    Medium *enemy2 = new Medium(350,200, difficult, ply);
//    enemy2->setPos(enemy2->pointList[0].x(), enemy2->pointList[0].y());
//    enemy2->setCommand(VERT);

//    Destroyer *enemy3= new Destroyer(50,550, difficult, ply);
//    enemy3->setPos(enemy3->pointList[0].x(), enemy3->pointList[0].y());
//    enemy3->setCommand(GUARD);

//    Medium *enemy4 = new Medium(800,600, difficult, ply);
//    enemy4->setPos(enemy4->pointList[0].x(), enemy4->pointList[0].y());

    QPixmap bground_img(QString(":/img/tex/tex_sand_01.png"));

    this->setBackgroundBrush(QBrush(bground_img));

//    this->addItem(water_1);
//    this->addItem(water_2);
//    this->addItem(bridge_1);
//    this->addItem(enemy2);
//    this->addItem(enemy3);
//    this->addItem(enemy4);
    this->addItem(ply);
}

Map::~Map()
{
    qDebug()<<"Robię destruktor map";
    ply = nullptr;
}

void Map::changeLevel()
{
    if(level == 1)
    {
        QList<QGraphicsItem*> all = items();
        qDebug()<<all.size();

        for(int i=0;i<all.size();i++)
        {
            if(typeid (*(all[i])) != typeid (Player))
            {
                delete all[i];
            }
        }
        ply->setPos(100,100);
        createFinalLevel();
        level++;
    }
}

void Map::createFinalLevel()
{
    Medium *enemy = new Medium(500,200, difficult, ply);
    enemy->setPos(enemy->pointList[0].x(), enemy->pointList[0].y());
    enemy->setCommand(PATROL);
    this->addItem(enemy);
    enemy->addStick();
    enemy->addPointToPath(500,400, enemy->pointList);
}




