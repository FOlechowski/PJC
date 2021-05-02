#ifndef PLAYER_H
#define PLAYER_H

#include <QKeyEvent>
#include <QDebug>
#include <QObject>
#include "tank.h"

class Player : public Tank
{
    Q_OBJECT

public:
    Player();

    void setPlayerName(QString Pname);
    void shot();
    void keyPressEvent(QKeyEvent * event);

public slots:

private:

    int bullets = 50;

    QString name;
    qreal angle = 0;
};

#endif // PLAYER_H
