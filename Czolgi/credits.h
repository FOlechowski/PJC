#ifndef CREDITS_H
#define CREDITS_H

#include <QObject>
#include <QDialog>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QMediaPlayer>
#include "button.h"

class Credits : public QDialog
{
    Q_OBJECT
public:
    Credits(QString ic_path);
    ~Credits();

    int w_width = 800;
    int w_height = 500;

    QString title = "O autorach...";
    QString main_text = "Nic tu nie ma...";

public slots:


private:
    Button* quit;

    QGraphicsView* win_view;
    QGraphicsScene* win_scene;

    QGraphicsTextItem* text;

};

#endif // CREDITS_H
