#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QDebug>
#include <QTimer>
#include "player.h"
#include "tank.h"

#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QList>

#define GUARD 'g'
#define PATROL 'p'

class Enemy : public Tank
{
    Q_OBJECT
public:

    Enemy();
    ~Enemy();

    void holdPos();
    bool check();
    void aim(float angle);
    void setCommand(char comm);
    void followPlayer();
    void addStick();

    bool obstacleInLine();

    void addPointToPath(int x, int y, QList<QPoint> &list);

    void goTo(int &pointer, QList<QPoint> &list);

    QList<QPoint> pointList;

public slots:
    void move();

protected:
    char command;
    Player *player;

private:
    QGraphicsRectItem *stick = NULL;
    QGraphicsTextItem *txt;

    int lastPosx = 0;
    int lastPosy = 0;

    int player_lastx;
    int player_lasty;

    int pointer = 0;
    int pr_pointer = 0;

    QList<QPoint> pursuitList;

    bool was_spotted = false;
};

#endif // ENEMY_H
