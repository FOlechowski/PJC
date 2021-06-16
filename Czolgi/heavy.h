#ifndef HEAVY_H
#define HEAVY_H

#include "enemy.h"

class Heavy : public Enemy
{
    Q_OBJECT
public:
    Heavy(qreal x, qreal y, int dif, Player* pl = NULL);
    void setPathTextures();
};

#endif // HEAVY_H
