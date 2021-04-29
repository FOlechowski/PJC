#include "game.h"
#include <QIcon>
#include "menu.h"
#include <QDebug>
#include <QMessageBox>

Game::Game(Menu* mn)
{
    //pointer to the main menu
    menu = mn;


    //set the options of the game widget window
    setFixedSize(QSize(mn->win_width, mn->win_height));
    setWindowTitle(mn->win_title);
    setWindowIcon(QIcon(mn->icon_path));

    //set the view in the widget
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
    QPixmap bground_img(mn->bckg_path);
    bground_img = bground_img.scaled(this->size(), Qt::IgnoreAspectRatio);      //scale background image to window size
    init_scene->setBackgroundBrush(QBrush(bground_img));

    //set the text input font
    QFont font("Calibri", 24);

    //set the line input text widget
    username = new QLineEdit(init_view);
    username->setPlaceholderText(QString("Wprowadź nazwę gracza..."));
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
    text -> setPlainText(QString("Wybierz poziom trudności:"));
    text -> setDefaultTextColor(Qt::white);
    text -> setFont(QFont("calibri", 28));
    int txPos = this->width()/2 - text->boundingRect().width()/2;
    text -> setPos(txPos, 200);

    init_scene->addItem(text);

    this->show();

}


void Game::create_player(QString name)
{
    player = new Player();
    player->setPlayerName(name);
}

void Game::draw_interface(Player* player)
{
    map_view = new QGraphicsView(this);
    map_view->setRenderHint(QPainter::HighQualityAntialiasing);
    map_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    map_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    map_view->setFixedSize(QSize(this->width(), this->height()-100));
    map_view->show();

    game_interfece = new QGraphicsView(this);
    game_interfece->setRenderHint(QPainter::HighQualityAntialiasing);
    game_interfece->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    game_interfece->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    game_interfece->setFixedSize(QSize(this->width(), 100));
    game_interfece->move(0,this->height()-100);
    game_interfece->show();

    map = new Map(player);

    map_view->setScene(map);
}

void Game::set_baron()
{
    diffic = easy;
    qDebug()<<diffic;
    qDebug()<<"Red Baron";

    QString name = username->text();

    if(!name.isEmpty())
    {
        create_player(name);
        init_view->close();
        draw_interface(player);
    }
    else
    {
        QMessageBox box;
        box.setWindowIcon(QIcon(menu->icon_path));
        box.setFixedSize(QSize(300,100));
        box.setText(QString("Wprowadź nazwę gracza!!!"));
        box.exec();
    }
}

void Game::set_kabaczek()
{
    diffic = medium;
    qDebug()<<diffic;
    qDebug()<<"Kabaczek";

    QString name = username->text();

    if(!name.isEmpty())
    {
        create_player(name);
        init_view->close();
        draw_interface(player);
    }
    else
    {
        QMessageBox box;
        box.setWindowIcon(QIcon(menu->icon_path));
        box.setFixedSize(QSize(300,100));
        box.setText(QString("Wprowadź nazwę gracza!!!"));
        box.exec();
    }
}

void Game::set_fiolet()
{
    diffic = hard;
    qDebug()<<diffic;
    qDebug()<<"Fiolet";

    QString name = username->text();

    if(!name.isEmpty())
    {
        create_player(name);
        init_view->close();
        draw_interface(player);
    }
    else
    {
        QMessageBox box;
        box.setWindowIcon(QIcon(menu->icon_path));
        box.setFixedSize(QSize(300,100));
        box.setText(QString("Wprowadź nazwę gracza!!!"));
        box.exec();
    }
}
