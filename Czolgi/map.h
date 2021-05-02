#ifndef MAP_H
#define MAP_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMediaPlayer>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QDebug>
#include "player.h"
#include "medium.h"

class Map: public QGraphicsScene
{

public:
    Map(Player* player, int diff);
    ~Map();

    int ms_width = 1000;
    int ms_height = 800;

    int difficult = 0;

public slots:

private:

    Player* ply;
    QGraphicsRectItem* bridge;
    QGraphicsRectItem* wall1;
    QGraphicsRectItem* wall2;
    QGraphicsRectItem* water;
};

#endif // MAP_H
