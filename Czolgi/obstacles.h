#ifndef OBSTACLES_H
#define OBSTACLES_H

#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QBrush>

class Obstacles : public QGraphicsPixmapItem
{
public:
    Obstacles();
};

class Water : public QGraphicsRectItem
{
public:
    Water();
};

class Bridge : public QGraphicsPixmapItem
{
public:
    Bridge();
};

class Rock : public QGraphicsPixmapItem
{
public:
    Rock();

};


#endif // OBSTACLES_H
