#ifndef EXPLOSIVEBULLET_H
#define EXPLOSIVEBULLET_H

#include "bullet.h"

class ExplosiveBullet : public Bullet
{
    Q_OBJECT
public:
    ExplosiveBullet(float ang, Tank* tank);

public slots:
    void removeExplosion();

protected:
    void Explode();
    bool bulletIsCollidig();

private:
     QGraphicsPixmapItem *explosion;
     QTimer *explosion_timer;

     bool explosion_is_set = false;
};

#endif // EXPLOSIVEBULLET_H
