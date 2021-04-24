#ifndef MAP_H
#define MAP_H


#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMediaPlayer>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QDebug>
#include "player.h"

class Map: public QGraphicsScene
{

public:
    Map();
    ~Map();

    int mv_width = 1000;
    int mv_height = 800;

    int ms_width = 1000;
    int ms_height = 800;

public slots:

private:

    QGraphicsView* map;
    Player* player;
    QGraphicsRectItem* bridge;
    QGraphicsRectItem* wall1;
    QGraphicsRectItem* wall2;
    QGraphicsRectItem* water;
};

#endif // MAP_H
