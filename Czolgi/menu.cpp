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
    delete intro;
    delete model;
    delete tree;
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
    connect(load_game, SIGNAL(clicked()), this, SLOT(loadGame()));
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
    connect(stay, SIGNAL(clicked()), dialog, SLOT(deleteLater()));
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
    connect(quit, SIGNAL(clicked()), cr_dialog, SLOT(deleteLater()));
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

void Menu::loadGame()
{
    dialog = new QDialog();
    dialog->setModal(true);
    QString path = game->getPath(ico);
    dialog->setWindowIcon(QIcon(path));
    dialog->setWindowTitle(QString("Wczytywanie gry"));
    dialog->setFixedSize(600,400);

    QVBoxLayout *m_layout = new QVBoxLayout(this);
    tree = new QTreeView;

    QPushButton *load = new QPushButton;
    connect(load, SIGNAL(clicked()), this, SLOT(loadFile()));
    load->setText("Wczytaj");
    load->setFont(QFont("calibri", 20));

    model = new QFileSystemModel;

    QStringList filters;
    filters <<"*.sav";

    model->setRootPath("D:/Testowy");
    model->setNameFilters(filters);
    model->setNameFilterDisables(false);

    tree->setModel(model);
    tree->setColumnHidden(1, true);
    tree->setColumnHidden(2, true);
    tree->setColumnWidth(0,250);
    tree->setColumnWidth(3,250);
    tree->setRootIndex(model->index("D:/Testowy"));

    m_layout->addWidget(tree);
    m_layout->addWidget(load);

    dialog->setLayout(m_layout);

    dialog->show();
}

void Menu::loadFile()
{
    QModelIndex index = tree->selectionModel()->currentIndex();
    QVariant data = tree->model()->data(index);
    QString f_name = data.toString();

    QFile file("D:/Testowy/"+f_name);

    if(file.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&file);
        while(!stream.atEnd())
        {
            QString line = stream.readLine();
            s_file[sp] = line;
            sp++;
        }
    }
    file.close();

    sp = 0;

    int lvl = s_file[sp++].rightRef(1).toInt();
    int dif = s_file[sp++].rightRef(1).toInt();

    QString type = s_file[sp].left(4);
    if(type == "Type")
    {
        int lenght = s_file[sp].length()-1;
        QString tname;

        while(s_file[sp][lenght] != "=")
        {
            tname = tname+s_file[sp][lenght--];
        }

        std::reverse(tname.begin(), tname.end());
        sp++;

        if(tname == "Player")
        {
            lenght = s_file[sp].length()-1;
            QString pname;
            while(s_file[sp][lenght] != "=")
            {
                pname = pname+s_file[sp][lenght--];
            }
            std::reverse(pname.begin(),pname.end());
            game->create_player(pname);
            sp++;

            int px;
            int py;


        }
    }
    //game->createMap(lvl,dif);
    //game->setInterface();
}


