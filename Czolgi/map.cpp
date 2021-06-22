#include "map.h"
#include "medium.h"
#include "destroyer.h"
#include "light.h"
#include "boss.h"
#include "heavy.h"
#include <QFile>
#include <QPainter>

Map::Map(Player* player, int diff, int lvl)
{
    difficult = diff;
    level = lvl;
    ply = player;

    this->setSceneRect(-50, 0, ms_width, ms_height);
    //this->safeToFile();
    this->setLevel(level);
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
    Medium *enemy = new Medium(500, 200, difficult, ply);
    enemy->setPos(enemy->pointList[0].x(), enemy->pointList[0].y());
    enemy->setCommand(PATROL);
    this->addItem(enemy);
    enemy->addStick();
    enemy->addPointToPath(500,400, enemy->pointList);
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
        Rock* rock_1 = new Rock;
        rock_1->setPos(750,100);
        rock_1->setScale(0.8);
        this->addItem(rock_1);

        UTrack* track = new UTrack;

        track->setPos(300,350);
        this->addItem(track);

        UEngine* engine = new UEngine;
        engine->setPos(200,350);
        this->addItem(engine);

        UArmor* armor = new UArmor;
        armor->setPos(69,420);
        this->addItem(armor);

        UChest* chest = new UChest;
        chest->setPos(220,50);
        this->addItem(chest);

        UHealth* health = new UHealth;
        health->setPos(500,70);
        this->addItem(health);

        ply->setFlag(QGraphicsItem::ItemIsFocusable);
        ply->setFocus();
        ply->setPos(0, 0);
        ply->setPointerToMap(this);

        Medium *enemy = new Medium(500,200, difficult, ply);
        enemy->setPos(enemy->pointList[0].x(), enemy->pointList[0].y());
        enemy->setCommand(GUARD);
        this->addItem(enemy);
        enemy->addStick();

        Medium *enemy2 = new Medium(600,300, difficult, ply);
        enemy2->setPos(enemy2->pointList[0].x(), enemy2->pointList[0].y());
        enemy2->setCommand(GUARD);
        this->addItem(enemy2);
        enemy2->addStick();

        QPixmap bground_img(QString(":/img/tex/tex_sand_01.png"));

        this->setBackgroundBrush(QBrush(bground_img));
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

void Map::setLevel(int lvl)
{
    if(lvl == 1)
        this->initialLevel();
    else
        this->changeLevel();
}
