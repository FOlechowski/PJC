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

    void setPlayerName(QString Pname);

    void keyPressEvent(QKeyEvent * event);

private:
    QString name;
    int angle = 0;
    int speed = 10;
};

#endif // PLAYER_H
