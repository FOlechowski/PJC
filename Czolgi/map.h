#ifndef MAP_H
#define MAP_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMediaPlayer>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QDebug>
#include "player.h"
#include "obstacles.h"
class Player;

class Map: public QGraphicsScene
{

public:
    Map(Player* player, int diff);
    ~Map();

<<<<<<< HEAD
=======
    int ms_width = 1800;
    int ms_height = 1500;

    int difficult = 0;
    //bool isonbridge();

>>>>>>> b374597b2e53b398723b4e0e096749c24b8ac731
public slots:

private:
    Player* ply;
    QGraphicsRectItem* wall1;
    QGraphicsRectItem* wall2;

    int ms_width = 1200;
    int ms_height = 1000;

    int difficult = 0;
};

#endif // MAP_H
