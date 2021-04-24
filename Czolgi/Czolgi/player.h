#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QGraphicsItem>
#include <QKeyEvent>
#include <QDebug>

class Player : public QGraphicsPixmapItem
{
public:
    Player();
    void keyPressEvent(QKeyEvent * event);
};

#endif // PLAYER_H
