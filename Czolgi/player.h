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
    QString PlayerTextures[24];
    int bullets = 50;

    QString name;
};

#endif // PLAYER_H
