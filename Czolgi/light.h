#ifndef LIGHT_H
#define LIGHT_H

#include "enemy.h"

class Light : public Enemy
{
    Q_OBJECT
public:
    Light(qreal x, qreal y, int dif, Player* pl = NULL);
    void setPath();
};

#endif // LIGHT_H
