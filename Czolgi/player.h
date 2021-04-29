#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QGraphicsItem>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QDebug>

class Player : public QGraphicsPixmapItem
{
public:
    Player();

    void setPlayerName(QString Pname);
    void shot();

    void keyPressEvent(QKeyEvent * event);

private:

    int bullets = 50;

    QString name;
    qreal angle = 0;
    qreal speed = 5;
};

#endif // PLAYER_H
