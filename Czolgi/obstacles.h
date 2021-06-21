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

class Rock : public Obstacles
{
public:
    Rock();

};

class UTrack : public Obstacles
{
public:
    UTrack();
};

class UEngine : public Obstacles
{
public:
    UEngine();
};

class UArmor : public Obstacles
{
public:
    UArmor();
};

class UChest : public Obstacles
{
public:
    UChest();
};

#endif // OBSTACLES_H
