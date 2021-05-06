#ifndef PLAYER_H
#define PLAYER_H

#include <QKeyEvent>
#include <QDebug>
#include <QObject>
#include "tank.h"
#include <QString>


class Player : public Tank
{
    Q_OBJECT

public:
    Player();

    void setPlayerName(QString Pname);
    void shot();
    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent *event);

public slots:

private:
    void addPlayerTextures();
    void moveForward(qreal m_distance, int m_angle);
    void moveBackward(qreal m_distance, int m_angle);
    void turnLeft(int &m_angle);
    void turnRight(int &m_angle);

    int bullets = 50;
    QString name;
    bool keyA, keyW, keyD, keyS;
};

#endif // PLAYER_H
