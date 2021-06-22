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

class Bridge : public Obstacles
{
public:
    Bridge();
};

class Rock : public Obstacles
{
public:
    Rock();

};

class Decoration1 : public Obstacles
{
public:
    Decoration1();

};

class Decoration2 : public Obstacles
{
public:
    Decoration2();

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

class UHealth : public Obstacles
{
 public:
    UHealth();
};

#endif // OBSTACLES_H
