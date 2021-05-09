#ifndef OBSTACLES_H
#define OBSTACLES_H

#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QBrush>

class obstacles : public QGraphicsPixmapItem
{
public:
    obstacles();
};

class water : public QGraphicsRectItem
{
public:
    water();
};

class bridge : public QGraphicsPixmapItem
{
public:
    bridge();
};

class rock : public QGraphicsPixmapItem
{
public:
    rock();

};


#endif // OBSTACLES_H
