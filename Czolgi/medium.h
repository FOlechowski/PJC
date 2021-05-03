#ifndef MEDIUM_H
#define MEDIUM_H

#include <QObject>
#include "enemy.h"

class Medium : public Enemy
{
    Q_OBJECT
public:
    Medium(qreal x, qreal y, int dif, Player* pl = NULL);

public slots:
    void move();
};

#endif // MEDIUM_H
