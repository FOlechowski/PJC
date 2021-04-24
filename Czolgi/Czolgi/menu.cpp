#include "menu.h"
#include <QIcon>

Game::Game(QWidget *parent) :QGraphicsView(parent)

{
    //define size and set icon, title
    setFixedSize(QSize(win_width, win_height));
    setWindowTitle(win_title);
    setWindowIcon(QIcon(icon_path));

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);   

}


void Game::play_music()
{
    //Intro sound
    intro = new QMediaPlayer;
    intro->setMedia(QUrl("qrc:/sound/snd/Intro3.WAV"));
   // intro->play();
}


void  Game::display_menu()
{
    //create new scene
    menu = new QGraphicsScene();
    menu->setSceneRect(0, 0, this->width(), this->height()-2);
    this->setScene(menu);

    //Add background image to the scene
    QPixmap bground_img(bckg_path);
    bground_img = bground_img.scaled(this->size(), Qt::IgnoreAspectRatio);      //scale background image to window size
    menu->setBackgroundBrush(QBrush(bground_img));

    play_music();

    //Add version information
    ver_inf = new QGraphicsTextItem();
    ver_inf->setPlainText(QString("Version alpha 0.0.5"));
    ver_inf->setDefaultTextColor(Qt::white);
    ver_inf->setFont(QFont("calibri", font_size));
    ver_inf->setPos(5, this->height() - 2*font_size);

    //Add Title
    title = new QGraphicsTextItem();
    title -> setPlainText(win_title);
    title -> setDefaultTextColor(Qt::white);
    title -> setFont(QFont("calibri", font_size*2));
    int txPos = this->width()/2 - title->boundingRect().width()/2;
    title -> setPos(txPos, 120);

    menu -> addItem(ver_inf);
    menu -> addItem(title);

    //Create some button below

    new_game = new Button(400, 80,QString("Nowa gra"));
    int ngbxPos = this->width()/2 - new_game->boundingRect().width()/2;
    int ngbyPos = 250;
    new_game->setPos(ngbxPos,ngbyPos);
    connect(new_game, SIGNAL(clicked()), this, SLOT(display_map()));
    menu->addItem(new_game);

    load_game = new Button(400, 80, QString("Wczytaj gre"));
    int lgbxPos = this->width()/2 - load_game->boundingRect().width()/2;
    int lgbyPos = 350;
    load_game->setPos(lgbxPos,lgbyPos);
    menu->addItem(load_game);

    info = new Button(400, 80, QString("Credits"));
    int cxPos = this->width()/2 - info->boundingRect().width()/2;
    int cyPos = 450;
    info->setPos(cxPos,cyPos);
    connect(info, SIGNAL(clicked()), this, SLOT(credits()));
    menu->addItem(info);

    quit_butt = new Button(400, 80, QString("Wyjdź z gry"));
    int qxPos = this->width()/2 - quit_butt->boundingRect().width()/2;
    int qyPos = 550;
    quit_butt->setPos(qxPos,qyPos);
    connect(quit_butt, SIGNAL(clicked()), this, SLOT(quit_ask()));
    menu->addItem(quit_butt);

}

void Game::quit_ask()
{
    //Przeniesc do nowej klasy PopupWindow #eksperymentalne

    dialog_scene->clear();

    QMediaPlayer leave_ask;
    leave_ask.setMedia(QUrl("qrc:/sound/snd/leave.WAV"));
    //leave_ask.play();

    dialog->setModal(true);
    dialog->setFixedSize(QSize(up_width,up_height));
    dialog->setWindowTitle(QString("Dezercja!!!"));

    dialog_view->setFixedSize(QSize(dialog->width(), dialog->height()));
    dialog_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    dialog_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    dialog_scene->setSceneRect(0, 0, dialog_view->width(), dialog_view->height()-2);
    dialog_view->setScene(dialog_scene);

    QPixmap quit_image(":/img/img/uncle_sam.png");
    quit_image = quit_image.scaled(dialog_view->size(), Qt::IgnoreAspectRatio);      //scale background image to window size
    dialog_scene->setBackgroundBrush(QBrush(quit_image));

    stay = new Button(300,80,"Wracam!");
    int xsPos = 200 - stay->boundingRect().width()/2;
    int ysPos = 250;
    stay->setPos(xsPos,ysPos);
    connect(stay, SIGNAL(clicked()), dialog, SLOT(close()));
    dialog_scene->addItem(stay);

    leave = new Button(300,80,"Uciekam!");
    int xlPos = 600 - leave->boundingRect().width()/2;
    int ylPos = 250;
    leave->setPos(xlPos,ylPos);
    connect(leave, SIGNAL(clicked()), this, SLOT(close()));
    dialog_scene->addItem(leave);

    dialog->exec();
}

void Game::credits()
{
    cr = new Credits(icon_path);
}

void Game::display_map()
{
    mp = new Map();
    this->hide();
}

Game::~Game()
{
    delete menu;
    delete dialog;
    delete dialog_view;
    delete dialog_scene;

    delete load_game;
    delete quit_butt;
    delete new_game;
    delete info;
    delete leave;
    delete stay;

    delete title;
    delete ver_inf;

    delete intro;
    delete cr;
    delete mp;
}

