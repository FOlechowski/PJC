#include "player.h"
#include <cmath>
#include "bullet.h"
#include "explosivebullet.h"
#include "map.h"

Player::Player()
{
    this->setPixmap(QPixmap(":/img/tex/p0.png"));
    this->setTransformOriginPoint(50,50);
    connect(timer_reload, SIGNAL(timeout()),this,SLOT(reload()));

    speed = 4;
    addPlayerTextures();
    rotate_angle = 0;
    rotate = 3;
    keyA = keyW = keyD = keyS = false;

    QTimer * player_timer = new QTimer();                              //start timer for it
    connect(player_timer, SIGNAL(timeout()),this,SLOT(movePlayer()));        //connect to the slot that will emitate the smooth movement
    player_timer->start(50);
}

Player::~Player()
{
    qDebug()<<"Robię destruktor playera";
    delete game;
    delete map;
    delete view;
}

void Player::setPlayerName(QString Pname)
{
    name = Pname;
}

void Player::shot()
{
    if(getAP() && !is_loading && APisloaded)
    {
        timer_reload->start(reload_time);
        is_loading = true;
        setAPshells(getAP()-1);
        updateAmmo();

    }else if(getHE() && !is_loading && !APisloaded)
    {
        timer_reload->start(reload_time);

        is_loading = true;
        setHEshells(getHE()-1);
        updateAmmo();
    }
}

void Player::setPointerToView(QGraphicsView *view)
{
    this->view = view;
}

void Player::setPointerToMap(Map *map)
{
    this->map = map;
}

void Player::savePlayer(QFile *file)
{
    QTextStream stream(file);
    stream << "Type =Player" <<'\n';
    stream << "Player name =" <<this->name<<'\n';
    stream << "Player pos =" <<this->x()<<","<< this->y() <<'\n';
    stream << "Player hp =" <<this->hp<<'\n';
    stream << "Player dmg =" <<this->dmg<<'\n';
    stream << "Player armor =" <<this->armor<<'\n';
    stream << "Normal bullets ="<<this->APShells<<'\n';
    stream << "Player e_bullets ="<<this->HEShells<<'\n';
    stream << "Player reaload time =" <<this->reload_time<<'\n';
    stream << "Tracks ="<<this->tracks<<'\n';
    stream << "Engine ="<<this->engine<<'\n';
    stream << "Speed ="<<this->speed<<'\n';
}

void Player::getPointerToGame(Game *game)
{
    this->game = game;
}

void Player::updateHpBar()
{
    game->modifyHpBar(false);
}

void Player::updateReloadBar()
{
    if(is_loading)
    {
    game->modifyReloadBar(timer_reload->remainingTime());
    }else
    {
        game->modifyReloadBar(0);
    }
}

void Player::updateAmmo()
{
    game->modifyAmmo();
}

bool Player::getAmmo()
{
    return APisloaded;
}

void Player::moveForward(qreal m_distance, int m_angle)
{

    Tank::move(cos(m_angle*M_PI/180)*m_distance,-sin(m_angle*M_PI/180)*m_distance);
}

void Player::moveBackward(qreal m_distance, int m_angle)
{

    Tank::move(-cos(m_angle*M_PI/180)*m_distance/2,sin(m_angle*M_PI/180)*m_distance/2);
}

void Player::turnLeft(int &m_angle)
{
    m_angle += rotate;
    if(m_angle>180)
    {
        m_angle=-(180-rotate);
    }
}

void Player::turnRight(int &m_angle)
{
    m_angle = float(m_angle);
    m_angle -= rotate;

    if(m_angle<-180)
    {
        m_angle=(180-rotate);
    }
}

void Player::upgradeSpeed()
{
    if(engine>-1 && engine <3)
    {
        speed += 1;
        engine += 1;
    }
    game->modifyUEngine(engine);
}

bool Player::checkCol()
{
    QList<QGraphicsItem*> colliding_items = collidingItems();
    bool isonbridge,isonwater,stick = false;

     for (int i = 0, n = colliding_items.size(); i < n; i++){
         if(typeid((*colliding_items[i])) == typeid(UTrack))
         {
             changeRotateAngle(5);
             upgradeTrack();
             scene()->removeItem(colliding_items[i]);
             delete colliding_items[i];
         }
         if(typeid((*colliding_items[i])) == typeid(UEngine))
         {

             upgradeSpeed();
             scene()->removeItem(colliding_items[i]);
             delete colliding_items[i];

         }
         if(typeid((*colliding_items[i])) == typeid(UArmor))
         {

             upgradeArmor();
             scene()->removeItem(colliding_items[i]);
             delete colliding_items[i];

         }
         if(typeid((*colliding_items[i])) == typeid(UChest))
         {

             setAPshells(getAP()+5);
             setHEshells(getHE()+5);
             updateAmmo();
             scene()->removeItem(colliding_items[i]);
             delete colliding_items[i];

         }
         if(typeid((*colliding_items[i])) == typeid(UHealth))
         {
             setHP(init_hp + 50);
             game->modifyHpBar(true);
             scene()->removeItem(colliding_items[i]);
             delete colliding_items[i];

         }

     }

    colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; i++){

        if(typeid((*colliding_items[i])) == typeid(Bridge)){
            isonbridge = true;
        }else{
            isonbridge = false;
        }
        if (typeid((*colliding_items[i])) == typeid(Water))
        {
            isonwater = true;
        }else{
            isonwater = false;
        }
        if (typeid((*colliding_items[i])) == typeid(QGraphicsRectItem) || typeid((*colliding_items[i])) == typeid(QGraphicsTextItem)
                || typeid((*colliding_items[i])) == typeid(Decoration1) || typeid((*colliding_items[i])) == typeid(Decoration2)){
            stick = true;
            //qDebug()<<"patykuje";
        }else{
            stick = false;
        }
    }

    if(!outOfMap()&&(colliding_items.size()==0||(isonbridge&&!isonwater)||(stick&&colliding_items.size()==1)||(stick&&!isonwater&&colliding_items.size()==2)||(stick&&!isonwater&&isonbridge&&colliding_items.size()==3))){
        return true;
    }else if(colliding_items.size()!=0){
        return false;
    }

}

bool Player::outOfMap()
{

    if(this->x()<-55||this->x()>=map->getWidth()-140||this->y()<-5||this->y()>=map->getHeight()-90)
    {
        return true;
    }else
    {
        return false;
    }
}

void Player::setAPshells(int number)
{
    if(number>=0)
    {
        APShells = number;
    }
}

void Player::setHEshells(int number)
{
    if(number>=0)
    {
        HEShells = number;
    }
}

void Player::setAP()
{
    APisloaded = true;
}

void Player::setHE()
{
    APisloaded = false;
}

int Player::getAP()
{
    return APShells;
}

int Player::getHE()
{
    return HEShells;
}

float Player::getArmor()
{
    return armor;
}

void Player::changeRotateAngle(int newAngle)
{
    rotate = newAngle;
    while(rotate_angle%newAngle){
        rotate_angle++;
    }
}

int Player::getInitHp()
{
    return init_hp;
}

void Player::loadPlayer(int hp, int dmg, float armor, int b, int eb, int rtime, int spd, int tr, int eng)
{
    this->hp = hp;
    this->dmg = dmg;
    this->armor = armor;
    this->APShells = b;
    this->HEShells = eb;
    this->reload_time = rtime;
    this->speed = spd;
    this->tracks = tr;
    this->engine = eng;
}

void Player::upgradeTrack()
{
    if(!tracks)
    {
        tracks += 1;
    }
    game->modifyUTracks(tracks);
}

void Player::upgradeArmor()
{
    if(armor == 0.5)
    {
       armor = 0.75;
    }
    game->modifyUArmor();
}

void Player::movePlayer()
{
    if(this->x() >= 1600 && this->y() >= 1050 && this->y() <= 1300)
    {
        this->map->changeLevel();
    }

    if (checkCol()&&!(keyA&&keyD)){
        bool aw,dw,as,ds = true;

        if(view!=nullptr){
            view->centerOn(this);
            view->show();
        }

        if(keyA){
            if(keyW){
                turnLeft(rotate_angle);
                moveForward(speed,rotate_angle);
                aw = false;
            }else if(keyS){
                turnLeft(rotate_angle);
                moveBackward(speed,rotate_angle);
                as =false;

            }else{
            turnLeft(rotate_angle);
            //turnLeft(rotate_angle);
            }
        }

        if(keyD){
            if(keyW){
                turnRight(rotate_angle);
                moveForward(speed,rotate_angle);
                dw = false;

            }else if(keyS){
                turnRight(rotate_angle);
                moveBackward(speed,rotate_angle);
                ds =false;

            }else{
            turnRight(rotate_angle);
            //turnRight(rotate_angle);
            }
        }

        if(keyW){
            if(keyA&&aw){
                moveForward(speed,rotate_angle);
                turnLeft(rotate_angle);


            }else if(keyD&&dw){
                moveForward(speed,rotate_angle);

                turnRight(rotate_angle);

            }else{
            moveForward(2*speed,rotate_angle);
            }
        }

        if(keyS){
            if(keyA&&as){
                moveBackward(speed,rotate_angle);
                turnLeft(rotate_angle);
            }else if(keyD&&ds){
                moveBackward(speed,rotate_angle);
                turnRight(rotate_angle);
            }else{
            moveBackward(2*speed,rotate_angle);
            }
        }
    }else{

        if(keyW&&!front_hit&&!back_hit&&!right_hit&&!left_hit){
            front_hit = true;
        }else if(keyS&&!front_hit&&!back_hit&&!right_hit&&!left_hit){
            back_hit = true;
        }else if(keyA&&!front_hit&&!back_hit&&!right_hit&&!left_hit){
            left_hit = true;
        }else if(keyD&&!front_hit&&!back_hit&&!right_hit&&!left_hit){
            right_hit = true;
        }

        if(front_hit&&keyS){
            moveBackward(5*speed,rotate_angle);
            if (checkCol()){
            front_hit=false;
            }
        }
        if(back_hit&&keyW){
            moveForward(3*speed,rotate_angle);
            if (checkCol()){
            back_hit=false;
            }
        }
        if(right_hit&&keyA){
            turnLeft(rotate_angle);
            if (checkCol()){
            right_hit=false;
            }
        }
        if(left_hit&&keyD){
            turnRight(rotate_angle);
            if (checkCol()){
            left_hit=false;
            }
        }

    }
    if(key1&&!APisloaded)
    {
        APisloaded = true;
        key1 = false;
        timer_reload->start(reload_time);
        is_loading = true;
        game->modifyAmmoFrame();
    }
    if(key2&&APisloaded)
    {
        APisloaded = false;
        key2 = false;
        timer_reload->start(reload_time);
        is_loading = true;
        game->modifyAmmoFrame();
    }


    if(keySpace)
    {
        if(getAP() && !is_loading && APisloaded)
        {
            Bullet *bullet = new Bullet(-rotate_angle*M_PI/180, this);
            bullet->setPos(x()+50,y()+35);
            scene()->addItem(bullet);
            shot();
        }else if (getHE() && !is_loading && !APisloaded)
        {
            ExplosiveBullet *explosivebullet = new ExplosiveBullet(-rotate_angle*M_PI/180, this);
            explosivebullet->setPos(x()+50,y()+35);
            scene()->addItem(explosivebullet);
            shot();
        }else if(!getHE()||!getAP())
        {
            qDebug()<<"koniec amunicji!";
        }

    }
    //qDebug()<<timer_reload->remainingTime();
    updateReloadBar();

    Tank::setTexture(-rotate_angle);

    if((this->pos()).y()>=450)
    {
    }
}

void Player::addPlayerTextures()
{
    tex_path[0] = ":/img/tex/p0.png";
    tex_path[1] = ":/img/tex/p15.png";
    tex_path[2] = ":/img/tex/p30.png";
    tex_path[3] = ":/img/tex/p45.png";
    tex_path[4] = ":/img/tex/p60.png";
    tex_path[5] = ":/img/tex/p75.png";
    tex_path[6] = ":/img/tex/p90.png";
    tex_path[7] = ":/img/tex/p105.png";
    tex_path[8] = ":/img/tex/p120.png";
    tex_path[9] = ":/img/tex/p135.png";
    tex_path[10] = ":/img/tex/p150.png";
    tex_path[11] = ":/img/tex/p165.png";
    tex_path[12] = ":/img/tex/p180.png";
    tex_path[13] = ":/img/tex/p-15.png";
    tex_path[14] = ":/img/tex/p-30.png";
    tex_path[15] = ":/img/tex/p-45.png";
    tex_path[16] = ":/img/tex/p-60.png";
    tex_path[17] = ":/img/tex/p-75.png";
    tex_path[18] = ":/img/tex/p-90.png";
    tex_path[19] = ":/img/tex/p-105.png";
    tex_path[20] = ":/img/tex/p-120.png";
    tex_path[21] = ":/img/tex/p-135.png";
    tex_path[22] = ":/img/tex/p-150.png";
    tex_path[23] = ":/img/tex/p-165.png";
}
