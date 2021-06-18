#include "menu.h"
#include "game.h"
#include <QIcon>


Menu::Menu(Game *parent) : QGraphicsView(parent)

{
    game = parent;
    this->setFixedSize(QSize(game->width(), game->height()));
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->display();
}

Menu::~Menu()
{
    delete menu;
    delete dialog_view;
    delete cr_dialog_view;
    delete intro;
    delete dialog;
    delete cr_dialog;
}


void Menu::play_music()
{
    //Intro sound
    intro = new QMediaPlayer;
    intro->setMedia(QUrl("qrc:/sound/snd/Intro3.WAV"));
    //intro->play();
}

void  Menu::display()
{
    //create new scene
    menu = new QGraphicsScene();
    menu->setSceneRect(0, 0, this->width(), this->height()-2);
    this->setScene(menu);

    //Add background image to the scene
    QString path = game->getPath(bck);
    QPixmap bground_img(path);
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
    path = game->getPath(tl);
    title -> setPlainText(path);
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
    connect(new_game, SIGNAL(clicked()), this, SLOT(start_game()));
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

    this->show();
}

void Menu::quit_ask()
{
    dialog = new QDialog();

    dialog->setModal(true);
    QString path = game->getPath(ico);
    dialog->setWindowIcon(QIcon(path));
    dialog->setWindowTitle(QString("Dezercja!!!"));

    QMediaPlayer leave_ask;
    leave_ask.setMedia(QUrl("qrc:/sound/snd/leave.WAV"));
    leave_ask.play();

    dialog->setFixedSize(QSize(800,400));
    dialog_view = new QGraphicsView(dialog);
    QGraphicsScene *dialog_scene = new QGraphicsScene(dialog_view);

    dialog_view->setFixedSize(QSize(dialog->width(), dialog->height()));
    dialog_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    dialog_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    dialog_scene->setSceneRect(0, 0, dialog_view->width(), dialog_view->height()-2);
    dialog_view->setScene(dialog_scene);

    dialog_view->show();

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
    connect(leave, SIGNAL(clicked()), this, SLOT(quit_all()));
    dialog_scene->addItem(leave);

    dialog->show();
}

void Menu::credits()
{
    cr_dialog = new QDialog;

    cr_dialog->setModal(true);
    QString path = game->getPath(ico);
    cr_dialog->setWindowIcon(QIcon(path));
    cr_dialog->setWindowTitle(QString("O autorach..."));

    cr_dialog->setFixedSize(QSize(800, 500));

    cr_dialog_view = new QGraphicsView(cr_dialog);

    QGraphicsScene *dialog_scene = new QGraphicsScene(cr_dialog_view);

    cr_dialog_view->setFixedSize(QSize(cr_dialog->width(), cr_dialog->height()));
    cr_dialog_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    cr_dialog_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    dialog_scene->setSceneRect(0, 0, cr_dialog->width(), cr_dialog->height()-2);
    cr_dialog_view->setScene(dialog_scene);
    cr_dialog_view->show();

    Button *quit = new Button(300, 80, "Powrot");
    int xsPos = cr_dialog->width()/2 - quit->boundingRect().width()/2;
    int ysPos = 250;
    quit->setPos(xsPos,ysPos);
    connect(quit, SIGNAL(clicked()), cr_dialog, SLOT(close()));
    dialog_scene->addItem(quit);

    QMediaPlayer comment;
    comment.setMedia(QUrl("qrc:/sound/snd/Nothing.WAV"));
    comment.play();

    cr_dialog->show();
}

void Menu::start_game()
{
    game->newGame();
}

void Menu::quit_all()
{
    dialog->close();
    dialog->deleteLater();

    game->close();
    game->deleteLater();
}


