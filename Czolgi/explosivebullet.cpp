#include "explosivebullet.h"
#include "cmath"
#include <QDebug>
#include "player.h"
#include <QGraphicsPixmapItem>
#include <boss.h>

ExplosiveBullet::ExplosiveBullet(float ang, Tank* tank)
{
    creator = tank;                                             //save the pointer of the object that created bullet
    angle = ang;                                                //set the value of the vector movement angle

    speed = 5;
    penetration = 40;

    qreal deg_angle = (angle*180)/M_PI;                                         //calculate angle in degrees

    this->setPixmap(QPixmap(":/img/tex/tex_bullet_01.png"));                    //set the texture for the bullet
    this->setTransformOriginPoint(20,5);                                        //set the rotating point at the middle of the Pixmap
    this->setRotation(deg_angle);                                               //rotate the texture to be parallel to the movement vector

    QTimer * timer = new QTimer();                                              //start timer for it
    connect(timer, SIGNAL(timeout()),this,SLOT(moveBullet()));                  //connect to the slot that will emitate the smooth movement
    timer->start(10);
}

void ExplosiveBullet::removeExplosion()
{
    explosion_timer->stop();
    delete explosion_timer;

    scene()->removeItem(explosion);
    delete explosion;

    scene()->removeItem(this);
    delete this;
}

void ExplosiveBullet::Explode()
{
    if(!explosion_is_set)
    {
        explosion = new QGraphicsPixmapItem();
        explosion->setPixmap(QPixmap(":/img/tex/explosion.png"));
        explosion->setPos(this->x()-35,this->y()-50);
        scene()->addItem(explosion);


        explosion_timer = new QTimer;
        connect(explosion_timer,SIGNAL(timeout()),this,SLOT(removeExplosion()));
        explosion_timer->start(100);

        explosion_is_set = true;
    }

    QList<QGraphicsItem*> colliding_items = explosion->collidingItems();

    for (int i = 0, n = colliding_items.size(); i < n; i++)
    {
        bool enemy = checkIfEnemy(colliding_items[i]);

        if(enemy)
        {
            hitted = dynamic_cast<Tank*>(colliding_items[i]);

            int root = sqrt(pow(explosion->x() - hitted->x(),2)+pow(explosion->y() - hitted->y(),2));

            int hp = hitted->getHP();

            if(root!=0)
            {
                hp = hp - 200/root;
                hitted->setHP(hp);
            }

            if(hp <= 0)
            {
                scene()->removeItem(hitted);
                delete hitted;
            }
        }
    }
}

bool ExplosiveBullet::bulletIsCollidig()
{
    QList<QGraphicsItem*> colliding_items = collidingItems();                                   //create Qlist of colliding items

    if(colliding_items.size() == 0)
        return false;

    for (int i = 0, n = colliding_items.size(); i < n; i++)                                     //check the whole list
    {
        bool enemy = checkIfEnemy(colliding_items[i]);

        if(enemy && (colliding_items[i] != creator))                                            //if type id is matching and the bullet didn't hit the creators
        {
            hitted = dynamic_cast<Tank*>(colliding_items[i]);                                   //safe pointer to the hitted element
            int dmg = creator->getDMG();
            hitted->modifyHP(dmg,penetration);
            int hp = hitted->getHP();

            if(hp <=0)
            {
                scene()->removeItem(hitted);
                delete hitted;
            }

            if(typeid(*(colliding_items[i])) == typeid(Boss))
            {
                Boss *P_Boss = dynamic_cast<Boss*>(colliding_items[i]);
                P_Boss->getHelp(P_Boss->x()-200, P_Boss->y()-200);
            }

            Explode();
            return true;
        }

        if(colliding_items[i] != creator && typeid(*(colliding_items[i])) != typeid(QGraphicsRectItem) && typeid(*(colliding_items[i])) != typeid(QGraphicsTextItem))
        {
            Explode();
            return true;
        }
    }
    return false;
}
