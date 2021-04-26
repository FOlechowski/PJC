#include "game.h"
#include <QIcon>
#include "menu.h"
#include <QDebug>

Game::Game(Menu* mn)
{
    menu = mn;

    setFixedSize(QSize(mn->win_width, mn->win_height));
    setWindowTitle(mn->win_title);
    setWindowIcon(QIcon(mn->icon_path));

    init_view = new QGraphicsView(this);
    init_view->setFixedSize(this->width(),this->height());
    init_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    init_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    init_scene = new QGraphicsScene;
    init_scene->setSceneRect(0, 0, this->width(), this->height()-2);
    init_view->setScene(init_scene);

    //Add background image to the scene
    QPixmap bground_img(mn->bckg_path);
    bground_img = bground_img.scaled(this->size(), Qt::IgnoreAspectRatio);      //scale background image to window size
    init_scene->setBackgroundBrush(QBrush(bground_img));

    red_baron = new Button(400,100,"Red Baron",init_scene);
    int RxPos = this->width()/2 - red_baron->boundingRect().width()/2;
    int RyPos = 200;
    red_baron->setPos(RxPos,RyPos);
    connect(red_baron, SIGNAL(clicked()), this, SLOT(set_baron()));
    init_scene->addItem(red_baron);

    kabaczek = new Button(400,100,"Kabaczek",init_scene);
    int KxPos = this->width()/2 - kabaczek->boundingRect().width()/2;
    int KyPos = 350;
    kabaczek->setPos(KxPos,KyPos);
    connect(kabaczek, SIGNAL(clicked()), this, SLOT(set_kabaczek()));
    init_scene->addItem(kabaczek);

    fiolet = new Button(400,100,"Fiolet",init_scene);
    int FxPos = this->width()/2 - fiolet->boundingRect().width()/2;
    int FyPos = 500;
    fiolet->setPos(FxPos,FyPos);
    connect(fiolet, SIGNAL(clicked()), this, SLOT(set_fiolet()));
    init_scene->addItem(fiolet);

    this->show();

}


void Game::create_player()
{
    player = new Player;

    QString name = QInputDialog::getText(this,QString("Wprowadz nazwe gracza"),QString("Nazwa gracza:"), QLineEdit::Normal);

    while(name.isEmpty())
    {
        name = QInputDialog::getText(this,QString("Wprowadz poprawną nazwe gracza"),QString("Nazwa gracza:"), QLineEdit::Normal);
    }

    player->setPlayerName(name);
}

void Game::draw_interface()
{
    layout = new QGridLayout(this);

    map_view = new QGraphicsView;
    map_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    map_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    map_view->setFixedSize(QSize(this->width(), this->height()-100));

    game_interfece = new QGraphicsView;
    game_interfece->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    game_interfece->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    game_interfece->setFixedSize(QSize(this->width(), 100));

    layout->addWidget(map_view, 0, 0, 0, 2);
    layout->addWidget(game_interfece, 1, 0, 1, 2);
}

void Game::set_baron()
{
    diffic = easy;
    qDebug()<<diffic;
    qDebug()<<"Red Baron";
    create_player();
}

void Game::set_kabaczek()
{
    diffic = medium;
    qDebug()<<diffic;
    qDebug()<<"Kabaczek";
    create_player();
}

void Game::set_fiolet()
{
    diffic = hard;
    qDebug()<<diffic;
    qDebug()<<"Fiolet";
    create_player();
}
