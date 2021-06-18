#ifndef BOSS_H
#define BOSS_H

#include "enemy.h"
#include "medium.h"

class Boss : public Enemy
{
    Q_OBJECT
public:
    Boss(qreal x, qreal y, int dif, Player* pl = nullptr);
    ~Boss();
    void setPathTextures();
    void getHelp(qreal x, qreal y);

private:
    int initial_hp;
    int game_dif;
    int m_counter = 2;

    int crd [4] = {100, 100, 100, 800};
};

#endif // BOSS_H
