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

    void changeLevel();
    void createFinalLevel();
    void safeToFile();
    void removeTrack();

public slots:

private:
    Player* ply;

    int ms_width = 1800;
    int ms_height = 1500;

    int difficult = 0;
    int level;
    UTrack* track = nullptr;
};

#endif // MAP_H
