#include "game.h"
#include <QIcon>
#include "menu.h"
#include <QDebug>
#include <QMessageBox>
#include <QScrollBar>
#include <QGraphicsPixmapItem>

Game::Game()
{
    setFixedSize(QSize(win_width, win_height));
    setWindowTitle(win_title);
    setWindowIcon(QIcon(icon_path));
}

Game::~Game()
{
    delete menu;
    delete player;
    delete map;
    delete init_view;
    delete map_view;
    delete game_interface;
    delete init_scene;
    delete text;
    delete hp_bar;
    delete interface_scene;
    delete frame;
    delete reload_bar;
}

void Game::drawInterface()
{
    map_view = new QGraphicsView(this);
    map_view->setRenderHint(QPainter::HighQualityAntialiasing);
    map_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    map_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    map_view->setFixedSize(QSize(this->width(), this->height()-150));
    map_view->show();

    game_interface = new QGraphicsView(this);
    game_interface->setRenderHint(QPainter::HighQualityAntialiasing);
    game_interface->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    game_interface->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    game_interface->setFixedSize(QSize(this->width(), 150));
    game_interface->move(0,this->height()-150);

    interface_scene = new QGraphicsScene;
    interface_scene->setSceneRect(0, 0, this->width(), 150);

    QPixmap intreface_bckg(this->interface_background);
    interface_scene->setBackgroundBrush(QBrush(intreface_bckg));

    QGraphicsPixmapItem* APShell = new QGraphicsPixmapItem;
    QGraphicsPixmapItem* HEShell = new QGraphicsPixmapItem;
    APShell->setPixmap(QPixmap(AP_icon));
    APShell->setScale(0.2);
    APShell->setPos(410,40);
    HEShell->setPixmap(QPixmap(HE_icon));
    HEShell->setScale(0.2);
    HEShell->setPos(480,40);

    interface_scene->addItem(APShell);
    interface_scene->addItem(HEShell);

    QGraphicsTextItem* APText = new QGraphicsTextItem;
    QGraphicsTextItem* HEText = new QGraphicsTextItem;
    APText->setFont(QFont("Calibri", 10));
    APText->setPlainText(QString("AP"));
    APText->setDefaultTextColor(Qt::white);
    APText->setPos(425, 15);
    HEText->setFont(QFont("Calibri", 10));
    HEText->setPlainText(QString("HE"));
    HEText->setDefaultTextColor(Qt::white);
    HEText->setPos(495, 15);

    interface_scene->addItem(APText);
    interface_scene->addItem(HEText);

    hp_bar = new QProgressBar();
    hp_bar->move(10,60);
    hp_bar->setMinimumSize(300,70);
    hp_bar->setTextVisible(true);
    interface_scene->addWidget(hp_bar);

    reload_bar = new QProgressBar();
    reload_bar->setOrientation(Qt::Vertical);
    reload_bar->move(550,20);
    reload_bar->setMinimumHeight(110);
    reload_bar->setMaximumWidth(15);
    interface_scene->addWidget(reload_bar);

    APNum = new QGraphicsTextItem;
    HENum = new QGraphicsTextItem;
    APNum->setFont(QFont("Calibri", 12));
    APNum->setDefaultTextColor(Qt::white);
    APNum->setPos(425, 105);
    HENum->setFont(QFont("Calibri", 12));
    HENum->setDefaultTextColor(Qt::white);
    HENum->setPos(495, 105);
    interface_scene->addItem(APNum);
    interface_scene->addItem(HENum);

    frame = new QGraphicsPixmapItem;
    frame->setPixmap(QPixmap(ramka));
    frame->setScale(0.2);
    frame->setPos(410,40);
    interface_scene->addItem(frame);

    QGraphicsTextItem* UTitle = new QGraphicsTextItem;
    UTitle->setFont(QFont("Calibri", 16));
    UTitle->setPlainText(QString("Ulepszenia:"));
    UTitle->setDefaultTextColor(Qt::white);
    UTitle->setPos(625, 10);
    interface_scene->addItem(UTitle);

    QFont font("Calibri", 18);
    player_name = new QGraphicsTextItem();
    player_name->setDefaultTextColor(Qt::white);
    player_name->setFont(font);
    player_name->setPos(5, 0);
    interface_scene->addItem(player_name);

    UTrack = new QGraphicsTextItem;
    UTrack->setFont(QFont("Calibri", 14));
    UTrack->setPlainText(QString("G??sienice: " + QString::number(0) + "/1"));
    UTrack->setDefaultTextColor(Qt::white);
    UTrack->setPos(625, 40);

    UEngine = new QGraphicsTextItem;
    UEngine->setFont(QFont("Calibri", 14));
    UEngine->setPlainText(QString("Silnik: " + QString::number(0) + "/1"));
    UEngine->setDefaultTextColor(Qt::white);
    UEngine->setPos(625, 70);

    UArmor = new QGraphicsTextItem;
    UArmor->setFont(QFont("Calibri", 14));
    UArmor->setPlainText(QString("Pancerz: " + QString::number(player->getArmor())));
    UArmor->setDefaultTextColor(Qt::white);
    UArmor->setPos(625, 100);

    interface_scene->addItem(UArmor);
    interface_scene->addItem(UEngine);
    interface_scene->addItem(UTrack);

    game_interface->setScene(interface_scene);
    game_interface->show();
}

void Game::create_player(QString name)
{
    player = new Player();
    player->setPlayerName(name);
    player->setInitialParameters(player->getInitHp(), 520, 0.5);
    player->getPointerToGame(this);
}

void Game::createMap(int lvl, int dif)
{
    map = new Map(this->player, dif, lvl);
}

void Game::displayMenu()
{
    menu = new Menu(this);
}

void Game::setInterface()
{
    drawInterface();

    map_view->setScene(map);
    player->setPointerToView(map_view);

    QString name = "";
    if(username != nullptr)
        name = username->text();

    player_name->setPlainText(QString("Gracz: " + name));

    hp_bar->setMinimum(0);
    hp_bar->setMaximum(player->getHP());
    hp_bar->setFormat(QString("%v / " + QString::number(hp_bar->maximum())));  

    hp_bar->setValue(hp_bar->maximum());

    reload_bar->setMinimum(-1);
    reload_bar->setMaximum(player->reloadTime()); 


    APNum->setPlainText(QString::number(player->getAP()));
    HENum->setPlainText(QString(QString::number(player->getHE())));
}

void Game::newGame()
{
        menu->close();    

        init_view = new QGraphicsView(this);
        init_view->setFixedSize(this->width(),this->height());
        init_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        init_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        //set the scene in the view
        init_scene = new QGraphicsScene;
        init_scene->setSceneRect(0, 0, this->width(), this->height()-2);

        //add scene to view
        init_view->setScene(init_scene);

        //Add background image to the scene
        QPixmap bground_img(this->bckg_path);
        bground_img = bground_img.scaled(this->size(), Qt::IgnoreAspectRatio);      //scale background image to window size
        init_scene->setBackgroundBrush(QBrush(bground_img));

        //set the text input font
        QFont font("Calibri", 24);

        //set the line input text widget
        username = new QLineEdit(init_view);
        username->setPlaceholderText(QString("Wprowad?? nazw?? gracza..."));
        username->setFixedSize(QSize(400,50));
        username->setMaxLength(20);
        username->setFont(font);
        username->setAlignment(Qt::AlignCenter);
        username->move(width()/2 - username->width()/2, 150);

        //add buttons
        red_baron = new Button(400,100,"Red Baron",init_scene);
        int RxPos = this->width()/2 - red_baron->boundingRect().width()/2;
        int RyPos = 250;
        red_baron->setPos(RxPos,RyPos);
        connect(red_baron, SIGNAL(clicked()), this, SLOT(set_baron()));
        init_scene->addItem(red_baron);

        kabaczek = new Button(400,100,"Kabaczek",init_scene);
        int KxPos = this->width()/2 - kabaczek->boundingRect().width()/2;
        int KyPos = 400;
        kabaczek->setPos(KxPos,KyPos);
        connect(kabaczek, SIGNAL(clicked()), this, SLOT(set_kabaczek()));
        init_scene->addItem(kabaczek);

        fiolet = new Button(400,100,"Fiolet",init_scene);
        int FxPos = this->width()/2 - fiolet->boundingRect().width()/2;
        int FyPos = 550;
        fiolet->setPos(FxPos,FyPos);
        connect(fiolet, SIGNAL(clicked()), this, SLOT(set_fiolet()));
        init_scene->addItem(fiolet);

        //Add some text
        QGraphicsTextItem *text = new QGraphicsTextItem;
        text -> setPlainText(QString("Wybierz poziom trudno??ci:"));
        text -> setDefaultTextColor(Qt::white);
        text -> setFont(QFont("calibri", 28));
        int txPos = this->width()/2 - text->boundingRect().width()/2;
        text -> setPos(txPos, 200);

        init_scene->addItem(text);

        init_view->show();

        menu->deleteLater();
        menu = nullptr;
}

QString Game::getPath(int path_type)
{
    QString path = "";

    switch (path_type)
    {
        case 0:
        path = bckg_path;
        break;

        case 1:
        path = icon_path;
        break;

        case 2:
        path = win_title;
        break;
    }

    return path;
}

void Game::set_baron()
{
    diffic = easy;

    QString name = username->text();

    if(!name.isEmpty())
    {
        create_player(name);
        init_view->close();
        init_view->deleteLater();
        init_view = nullptr;

        createMap(1,diffic);
        setInterface();
    }
    else
    {
        QMessageBox box;
        box.setWindowIcon(QIcon(this->icon_path));
        box.setFixedSize(QSize(300,100));
        box.setText(QString("Wprowad?? nazw?? gracza!!!"));
    }
}

void Game::set_kabaczek()
{
    diffic = medium;

    QString name = username->text();

    if(!name.isEmpty())
    {
        create_player(name);
        init_view->close();
        init_view->deleteLater();
        init_view = nullptr;

        createMap(1,diffic);
        setInterface();
    }
    else
    {
        QMessageBox box;
        box.setWindowIcon(QIcon(this->icon_path));
        box.setFixedSize(QSize(300,100));
        box.setText(QString("Wprowad?? nazw?? gracza!!!"));
    }
}

void Game::set_fiolet()
{
    diffic = hard;

    QString name = username->text();

    if(!name.isEmpty())
    {
        create_player(name);
        init_view->close();
        init_view->deleteLater();
        init_view = nullptr;

        createMap(1,diffic);
        setInterface();
    }
    else
    {
        QMessageBox box;
        box.setWindowIcon(QIcon(this->icon_path));
        box.setFixedSize(QSize(300,100));
        box.setText(QString("Wprowad?? nazw?? gracza!!!"));
    }
}

void Game::keyReleaseEvent(QKeyEvent *event)
{
    if(player != nullptr)
    {
        if(event->key() == Qt::Key_W){
            player->keyW = false;
            //qDebug()<<"released W";
        }
        if(event->key() == Qt::Key_D){
            player->keyD = false;
            //qDebug()<<"released D";
        }
        if(event->key() == Qt::Key_A){
            player->keyA = false;
            //qDebug()<<"released A";
        }
        if(event->key() == Qt::Key_S){
            player->keyS = false;
            //qDebug()<<"released S";
        }
        if(event->key() == Qt::Key_Space)
        {
            player->keySpace = false;
        }
        if(event->key() == Qt::Key_1)
        {
            player->key1 = false;

        }
        if(event->key() == Qt::Key_2)
        {
            player->key2 = false;

        }
    }
}

void Game::modifyHpBar(bool upgrade)
{
    if(upgrade)
    {
        hp_bar->setMaximum(player->getHP());
        hp_bar->setFormat(QString("%v / " + QString::number(hp_bar->maximum())));
    }
    hp_bar->setValue(player->getHP());
}


void Game::modifyReloadBar(int time)
{
    reload_bar->setValue(2000-time);
    reload_bar->setMaximum(player->reloadTime());

}

void Game::modifyAmmo()
{
    APNum->setPlainText(QString::number(player->getAP()));
    HENum->setPlainText(QString(QString::number(player->getHE())));
}

void Game::modifyAmmoFrame()
{
    if(player->getAmmo())
    {
        frame->setPos(410,40);

    }else
    {
        frame->setPos(480,40);
    }
}

void Game::modifyUTracks(int number)
{
    UTrack->setPlainText(QString("G??sienice: " + QString::number(number) + "/1"));
}

void Game::modifyUEngine(int number)
{
    UEngine->setPlainText(QString("Silnik: " + QString::number(number) + "/1"));
}

void Game::modifyUArmor()
{
    UArmor->setPlainText(QString("Pancerz: " + QString::number(player->getArmor())));
}

void Game::keyPressEvent(QKeyEvent *event){
//qDebug()<<colliding_items;
//grabKeyboard();
    if(player != nullptr)
    {
        if(event->key() == Qt::Key_A)
        {
            player->keyA = true;
            //qDebug()<<"pressed A";
        }

        if(event->key() == Qt::Key_D)
        {
            player->keyD = true;
            //qDebug()<<"pressed D";
        }

        if(event->key() == Qt::Key_W)
        {
            player->keyW = true;
            //qDebug()<<"pressed W";
        }

        if(event->key() == Qt::Key_S)
        {
            player->keyS = true;
            //qDebug()<<"pressed S";
        }
        if(event->key() == Qt::Key_Space)
        {
            player->keySpace = true;
        }
        if(event->key() == Qt::Key_1)
        {
            player->key1 = true;

        }
        if(event->key() == Qt::Key_2)
        {
            player->key2 = true;

        }
    }
}

void Game::endGame(bool win)
{
    QMessageBox* end = new QMessageBox;
    if(win)
    {
        end->setText(QString("Gratulacje ??o??nierzu!"));
        end->exec();
    }
    else
    {
        map->removeItem(player);
        end->setText(QString("Koniec gry ??o??nierzu!"));
        end->exec();
        player->deleteLater();
    }

}
