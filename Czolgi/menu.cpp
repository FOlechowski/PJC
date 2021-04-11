#include "menu.h"
#include <QIcon>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QBrush>
#include <QPixmap>
#include <QDialog>
#include "button.h"

Menu::Menu(QWidget *parent, int w_size, int h_size) :QGraphicsView(parent)

{
    //define size and set icon, title
    setFixedSize(QSize(w_size, h_size));
    setWindowTitle(QString("CZOLGI WARS"));
    setWindowIcon(QIcon(":/img/img/icon.png"));

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);   

}

void  Menu::display_menu()
{
    //create new scene
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, this->width(), this->height()-2);
    this->setScene(scene);

    //Add background image to the scene
    QPixmap bground_img(":/img/img/background_02.png");
    bground_img = bground_img.scaled(this->size(), Qt::IgnoreAspectRatio);      //scale background image to window size
    scene->setBackgroundBrush(QBrush(bground_img));

    int font_size = 32;

    QGraphicsTextItem* ver_inf = new QGraphicsTextItem();
    ver_inf->setParent(this);
    ver_inf->setPlainText(QString("Version alpha 0.0.2"));
    ver_inf->setDefaultTextColor(Qt::white);
    ver_inf->setFont(QFont("calibri", font_size));
    ver_inf->setPos(5, this->height() - 2*font_size);

    //Add Title
    QGraphicsTextItem* title = new QGraphicsTextItem();
    title->setParent(this);
    title -> setPlainText(QString("CZOLGI WARS"));
    title -> setDefaultTextColor(Qt::white);
    title -> setFont(QFont("calibri", font_size*2));
    int txPos = this->width()/2 - title->boundingRect().width()/2;
    title -> setPos(txPos, 120);

    scene -> addItem(ver_inf);
    scene -> addItem(title);

    button* new_game = new button(400, 80,QString("Nowa gra"), this);
    int ngbxPos = this->width()/2 - new_game->boundingRect().width()/2;
    int ngbyPos = 250;
    new_game->setPos(ngbxPos,ngbyPos);
    scene->addItem(new_game);

    button* load_game = new button(400, 80, QString("Wczytaj gre"), this);
    int lgbxPos = this->width()/2 - load_game->boundingRect().width()/2;
    int lgbyPos = 350;
    load_game->setPos(lgbxPos,lgbyPos);
    scene->addItem(load_game);

    button* credits = new button(400, 80, QString("Credits"), this);
    int cxPos = this->width()/2 - credits->boundingRect().width()/2;
    int cyPos = 450;
    credits->setPos(cxPos,cyPos);
    scene->addItem(credits);

    button* quit = new button(400, 80, QString("Wyjdź z gry"), this);
    int qxPos = this->width()/2 - quit->boundingRect().width()/2;
    int qyPos = 550;
    quit->setPos(qxPos,qyPos);
    connect(quit, SIGNAL(clicked()), this, SLOT(quit_ask()));
    scene->addItem(quit);

}

void Menu::quit_ask()
{
    quit = new QDialog(this);
    quit->setModal(true);
    quit->setFixedSize(QSize(800,400));
    quit->setWindowTitle(QString("Dezercja!!!"));

    quit_view = new QGraphicsView;
    quit_view->setParent(quit);
    quit_view->setFixedSize(QSize(quit->width(),quit->height()));
    quit_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    quit_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    quit_scene = new QGraphicsScene(quit_view);
    quit_scene->setSceneRect(0, 0, quit_view->width(), quit_view->height()-2);
    quit_view->setScene(quit_scene);

    QPixmap quit_image(":/img/img/uncle_sam.png");
    quit_image = quit_image.scaled(quit_view->size(), Qt::IgnoreAspectRatio);      //scale background image to window size
    quit_scene->setBackgroundBrush(QBrush(quit_image));

    quit->exec();
}

Menu::~Menu()
{

}

