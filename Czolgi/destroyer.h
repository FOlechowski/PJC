#ifndef DESTROYER_H
#define DESTROYER_H

#include "enemy.h"

class Destroyer : public Enemy
{
    Q_OBJECT
public:
    Destroyer(qreal x, qreal y, int dif, Player* pl = NULL);
    void setPath();

public slots:

};

#endif // DESTROYER_H
