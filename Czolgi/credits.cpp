#include "credits.h"
#include <QIcon>

Credits::Credits(QString ic_path)
{

    this->setModal(true);
    this->setWindowIcon(QIcon(ic_path));
    this->setWindowTitle(title);

    this->setFixedSize(QSize(w_width,w_height));

    win_view = new QGraphicsView(this);
    win_scene = new QGraphicsScene(win_view);

    win_view->setFixedSize(QSize(this->width(), this->height()));
    win_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    win_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    win_scene->setSceneRect(0, 0, this->width(), this->height()-2);
    win_view->setScene(win_scene);

    quit = new Button(300, 80, "Powrot");
    int xsPos = this->width()/2 - quit->boundingRect().width()/2;
    int ysPos = 250;
    quit->setPos(xsPos,ysPos);
    connect(quit, SIGNAL(clicked()), this, SLOT(close()));
    win_scene->addItem(quit);

    QMediaPlayer comment;
    comment.setMedia(QUrl("qrc:/sound/snd/Nothing.WAV"));
    comment.play();

    this->exec();

}

Credits::~Credits()
{
    delete quit;

    delete win_view;
    delete win_scene;

    delete text;
}
