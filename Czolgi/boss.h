#ifndef BOSS_H
#define BOSS_H

#include "enemy.h"

class Boss : public Enemy
{
    Q_OBJECT
public:
    Boss(qreal x, qreal y, int dif, Player* pl = NULL);
    void setPath();
};

#endif // BOSS_H
