#include "map.h"
#include "medium.h"
#include "destroyer.h"
#include "light.h"
#include "boss.h"
#include "heavy.h"
#include <QFile>
#include <QPainter>

Map::Map(Player* player, int diff)
{
    difficult = diff;
    level = 1;
    ply = player;

    this->setSceneRect(-50, 0, ms_width, ms_height);
    this->safeToFile();
    this->initialLevel();
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

    Rock* rock_1 = new Rock;
    rock_1->setPos(200,200);
    rock_1->setScale(0.7);
    this->addItem(rock_1);

    Rock* rock_2 = new Rock;
    rock_2->setPos(1000,200);
    rock_2->setScale(0.7);
    this->addItem(rock_2);

    Rock* rock_3 = new Rock;
    rock_3->setPos(200,1000);
    rock_3->setScale(0.7);
    this->addItem(rock_3);

    Rock* rock_4 = new Rock;
    rock_4->setPos(1000,1000);
    rock_4->setScale(0.7);
    this->addItem(rock_4);

    UChest* chest_1 = new UChest;
    chest_1->setPos(30,200);
    this->addItem(chest_1);

    UChest* chest_2 = new UChest;
    chest_2->setPos(1600,200);
    this->addItem(chest_2);

    UChest* chest_3 = new UChest;
    chest_3->setPos(1600,1200);
    this->addItem(chest_3);

    UChest* chest_4 = new UChest;
    chest_4->setPos(30,1200);
    this->addItem(chest_4);

    UHealth* health = new UHealth;
    health->setPos(100,200);
    this->addItem(health);

    Medium *enemy = new Medium(500, 200, difficult, ply);
    enemy->setPos(enemy->pointList[0].x(), enemy->pointList[0].y());
    enemy->setCommand(PATROL);
    this->addItem(enemy);
    enemy->addStick();
    enemy->addPointToPath(500,400, enemy->pointList);

        Boss *boss = new Boss(800,600,difficult,ply);
        boss->setPos(boss->pointList[0].x(), boss->pointList[0].y());
        boss->setCommand(PATROL);
        boss->addPointToPath(1100,600,boss->pointList);
        boss->addPointToPath(1100,900,boss->pointList);
        boss->addPointToPath(800,900,boss->pointList);
        this->addItem(boss);
        boss->addStick();
}

void Map::safeToFile()
{
    QFile file("D:/Testowy/test2.sav");
    QTextStream stream(&file);

    if(file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
    {
        stream << "Level =" << this->level <<'\n';
        stream << "Dif =" << this->difficult <<'\n';
    }
    file.close();

    QList<QGraphicsItem*> all = items();

    for(int i=0;i<all.size();i++)
    {
        if(file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
        {
            if(typeid(*(all[i])) == typeid(Player))
            {
                ply->savePlayer(&file);
            }

            else if(typeid (*all[i]) == typeid (Boss) || typeid (*all[i]) == typeid (Medium) || typeid (*all[i]) == typeid (Light) || typeid (*all[i]) == typeid (Heavy) || typeid (*all[i]) == typeid (Destroyer))
            {
                QString name = typeid (*all[i]).name();
                Enemy *enemy = dynamic_cast<Enemy*>(all[i]);
                enemy->saveEnemy(&file, name);
            }

            file.close();
        }
    }
}

void Map::initialLevel()
{
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
    //Rocks
     {
        Rock* rock_1 = new Rock;
        rock_1->setPos(750,100);
        rock_1->setScale(0.6);
        this->addItem(rock_1);

        Rock* rock_2 = new Rock;
        rock_2->setPos(250,120);
        rock_2->setScale(0.3);
        this->addItem(rock_2);

        Rock* rock_3 = new Rock;
        rock_3->setPos(50,500);
        rock_3->setScale(0.3);
        this->addItem(rock_3);

        Rock* rock_4 = new Rock;
        rock_4->setPos(170,430);
        rock_4->setScale(0.35);
        this->addItem(rock_4);

        Rock* rock_5 = new Rock;
        rock_5->setPos(690,550);
        rock_5->setScale(0.3);
        this->addItem(rock_5);

        Rock* rock_6 = new Rock;
        rock_6->setPos(270,820);
        rock_6->setScale(0.5);
        this->addItem(rock_6);

        Rock* rock_7 = new Rock;
        rock_7->setPos(25,730);
        rock_7->setScale(0.3);
        this->addItem(rock_7);

        Rock* rock_8 = new Rock;
        rock_8->setPos(130,1100);
        rock_8->setScale(0.3);
        this->addItem(rock_8);

        Rock* rock_9 = new Rock;
        rock_9->setPos(15,1260);
        rock_9->setScale(0.3);
        this->addItem(rock_9);

        Rock* rock_10 = new Rock;
        rock_10->setPos(350,1380);
        rock_10->setScale(0.3);
        this->addItem(rock_10);

        Rock* rock_11 = new Rock;
        rock_11->setPos(750,1350);
        rock_11->setScale(0.65);
        this->addItem(rock_11);

        Rock* rock_12 = new Rock;
        rock_12->setPos(1080,1220);
        rock_12->setScale(0.35);
        this->addItem(rock_12);

        Rock* rock_13 = new Rock;
        rock_13->setPos(1110,775);
        rock_13->setScale(0.3);
        this->addItem(rock_13);

        Rock* rock_14 = new Rock;
        rock_14->setPos(1070,290);
        rock_14->setScale(0.35);
        this->addItem(rock_14);

        Rock* rock_15 = new Rock;
        rock_15->setPos(1430,20);
        rock_15->setScale(0.4);
        this->addItem(rock_15);

        Rock* rock_16 = new Rock;
        rock_16->setPos(1580,400);
        rock_16->setScale(0.6);
        this->addItem(rock_16);

        Rock* rock_17 = new Rock;
        rock_17->setPos(1580,1080);
        rock_17->setScale(0.5);
        this->addItem(rock_17);

        Rock* rock_18 = new Rock;
        rock_18->setPos(1580,1280);
        rock_18->setScale(0.5);
        this->addItem(rock_18);
    }

    //Decorations
    {
        Decoration1* dec_1 = new Decoration1;
        dec_1->setPos(-40,530);
        dec_1->setScale(0.4);
        this->addItem(dec_1);

        Decoration1* dec_2 = new Decoration1;
        dec_2->setPos(595,15);
        dec_2->setScale(0.4);
        this->addItem(dec_2);

        Decoration1* dec_3 = new Decoration1;
        dec_3->setPos(1515,325);
        dec_3->setScale(0.4);
        this->addItem(dec_3);

        Decoration1* dec_4 = new Decoration1;
        dec_4->setPos(520,1380);
        dec_4->setScale(0.4);
        this->addItem(dec_4);

        Decoration1* dec_5 = new Decoration1;
        dec_5->setPos(1165,705);
        dec_5->setScale(0.4);
        this->addItem(dec_5);

        Decoration1* dec_6 = new Decoration1;
        dec_6->setPos(120,230);
        dec_6->setScale(0.4);
        dec_6->setRotation(132);
        this->addItem(dec_6);

        Decoration2* bush_1 = new Decoration2;
        bush_1->setPos(320,20);
        bush_1->setScale(0.6);
        this->addItem(bush_1);

        Decoration2* bush_2 = new Decoration2;
        bush_2->setPos(50,350);
        bush_2->setScale(0.6);
        this->addItem(bush_2);

        Decoration2* bush_3 = new Decoration2;
        bush_3->setPos(300,740);
        bush_3->setScale(0.6);
        this->addItem(bush_3);

        Decoration2* bush_4 = new Decoration2;
        bush_4->setPos(30,1370);
        bush_4->setScale(0.6);
        this->addItem(bush_4);

        Decoration2* bush_5 = new Decoration2;
        bush_5->setPos(220,1050);
        bush_5->setScale(0.6);
        this->addItem(bush_5);

        Decoration2* bush_6 = new Decoration2;
        bush_6->setPos(600,1400);
        bush_6->setScale(0.6);
        this->addItem(bush_6);

        Decoration2* bush_7 = new Decoration2;
        bush_7->setPos(855,1140);
        bush_7->setScale(0.6);
        this->addItem(bush_7);

        Decoration2* bush_8 = new Decoration2;
        bush_8->setPos(1270,775);
        bush_8->setScale(0.55);
        this->addItem(bush_8);

        Decoration2* bush_9 = new Decoration2;
        bush_9->setPos(1135,230);
        bush_9->setScale(0.6);
        this->addItem(bush_9);

        Decoration2* bush_10 = new Decoration2;
        bush_10->setPos(660,110);
        bush_10->setScale(0.6);
        this->addItem(bush_10);

       }


    //Upgrades
    {
        UTrack* track = new UTrack;
        track->setPos(1120,100);
        this->addItem(track);

        UEngine* engine = new UEngine;
        engine->setPos(140,1325);
        this->addItem(engine);

        UArmor* armor = new UArmor;
        armor->setPos(1035,1375);
        this->addItem(armor);

        UChest* chest_1 = new UChest;
        chest_1->setPos(25,950);
        this->addItem(chest_1);

        UChest* chest_2 = new UChest;
        chest_2->setPos(1500,760);
        this->addItem(chest_2);

        UChest* chest_3 = new UChest;
        chest_3->setPos(1580,1220);
        this->addItem(chest_3);

        UHealth* health = new UHealth;
        health->setPos(810,960);
        this->addItem(health);

    }

        ply->setFlag(QGraphicsItem::ItemIsFocusable);
        ply->setFocus();
        ply->setPos(0, 0);
        ply->setPointerToMap(this);

        Destroyer *enemy = new Destroyer(270,1215, difficult, ply);
        enemy->setPos(enemy->pointList[0].x(), enemy->pointList[0].y());
        enemy->setCommand(GUARD);
        this->addItem(enemy);
        enemy->addStick();

        Medium *enemy2 = new Medium(430,40, difficult, ply);
        enemy2->setPos(enemy2->pointList[0].x(), enemy2->pointList[0].y());
        enemy2->setCommand(PATROL);
        enemy2->addPointToPath(400,390,enemy2->pointList);
        enemy2->addPointToPath(700,390,enemy2->pointList);
        this->addItem(enemy2);
        enemy2->addStick();

        Destroyer *enemy3 = new Destroyer(920,210, difficult, ply);
        enemy3->setPos(enemy3->pointList[0].x(), enemy3->pointList[0].y());
        enemy3->setCommand(GUARD);
        this->addItem(enemy3);
        enemy3->addStick();

        Light *enemy4 = new Light(1350,160, difficult, ply);
        enemy4->setPos(enemy4->pointList[0].x(), enemy4->pointList[0].y());
        enemy4->setCommand(PATROL);
        enemy4->addPointToPath(1350,440,enemy4->pointList);
        this->addItem(enemy4);
        enemy4->addStick();

        Heavy *enemy5 = new Heavy(1450,1200, difficult, ply);
        enemy5->setPos(enemy5->pointList[0].x(), enemy5->pointList[0].y());
        enemy5->setCommand(GUARD);
        this->addItem(enemy5);
        enemy5->addStick();

        Light *enemy6 = new Light(900,670, difficult, ply);
        enemy6->setPos(enemy6->pointList[0].x(), enemy6->pointList[0].y());
        enemy6->setCommand(GUARD);
        this->addItem(enemy6);
        enemy6->addStick();

        //enemy->addPointToPath(500,400, enemy->pointList);



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

int Map::getWidth()
{
    return ms_width;
}

int Map::getHeight()
{
    return ms_height;
}
