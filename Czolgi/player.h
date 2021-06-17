#ifndef PLAYER_H
#define PLAYER_H

#include <QKeyEvent>
#include <QDebug>
#include <QObject>
#include "tank.h"
#include <QString>
#include "obstacles.h"
#include "game.h"


class Game;

class Player : public Tank
{
    Q_OBJECT

public:
    Player();

    void setPlayerName(QString Pname);
    void shot();
    void setPointerToView(QGraphicsView *view);
    bool keyA, keyW, keyD, keyS,keySpace = false;
public slots:

private:
    void addPlayerTextures();
    void moveForward(qreal m_distance, double m_angle);
    void moveBackward(qreal m_distance, double m_angle);
    void turnLeft(double &m_angle);
    void turnRight(double &m_angle);
    bool checkCol();
    QGraphicsView *view = nullptr;
    int bullets = 50;
    QString name;

    bool front_hit, back_hit, right_hit, left_hit = false;
private slots:
    void movePlayer();

};

#endif // PLAYER_H
