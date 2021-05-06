#include "quitwindow.h"
#include "button.h"
#include <QIcon>

QuitWindow::QuitWindow(QGraphicsView* window, QString ic_path)
{

    this->setModal(true);
    this->setWindowIcon(QIcon(ic_path));
    this->setWindowTitle(title);
    menu = window;

    QMediaPlayer leave_ask;
    leave_ask.setMedia(QUrl("qrc:/sound/snd/leave.WAV"));
    leave_ask.play();

    this->setFixedSize(QSize(up_width,up_height));
    dialog_view = new QGraphicsView(this);
    dialog_scene = new QGraphicsScene(dialog_view);

    dialog_view->setFixedSize(QSize(this->width(), this->height()));
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
    connect(stay, SIGNAL(clicked()), this, SLOT(close()));
    dialog_scene->addItem(stay);

    leave = new Button(300,80,"Uciekam!");
    int xlPos = 600 - leave->boundingRect().width()/2;
    int ylPos = 250;
    leave->setPos(xlPos,ylPos);
    connect(leave, SIGNAL(clicked()), this, SLOT(quit_all()));
    dialog_scene->addItem(leave);

    this->exec();

}



QuitWindow::~QuitWindow()
{
    delete stay;
    delete leave;
}

void QuitWindow::quit_all()
{
    this->close();
    menu->close();
}
