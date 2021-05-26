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

#define VERT 'v'
#define HORIZON 'h'
#define GUARD 'g'
#define PATROL 'p'

class Enemy : public Tank
{
    Q_OBJECT
public:

    Enemy();

    void holdPos();
    void patrolPathVerticaly(qreal end);
    void patrolPathHorizontaly(qreal end);
    bool check();
    void aim(float angle);
    void setCommand(char comm);
    void followPlayer();
    void addStick();
    bool obstacleInLine();
    void avoidObstacle();

    void addPointToPath(int x, int y);

    void goTo();

    bool timer_was_set = false;
    QList<QPoint> pointList;

public slots:
    void move();
    void comeBack();

protected:
    char command;
    Player *player;

private:
    QTimer *watchdog = new QTimer(this);
    QGraphicsRectItem *stick = NULL;

    int lastPosx = 0;
    int lastPosy = 0;

    int player_lastx;
    int player_lasty;

    int pointer = 0;

    bool reverso = false;
    bool was_spotted = false;
};

#endif // ENEMY_H
