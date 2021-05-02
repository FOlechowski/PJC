#ifndef QUITWINDOW_H
#define QUITWINDOW_H

#include <QObject>
#include <QDialog>
#include <QGraphicsView>


#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QMediaPlayer>
#include "button.h"


class QuitWindow : public QDialog
{
    Q_OBJECT
public:
    QuitWindow(QGraphicsView* window, QString ic_path);
    ~QuitWindow();
    QGraphicsView* menu;

    int up_width = 800;
    int up_height = 400;

    QString title = "Dezercja";
public slots:
    void quit_all();

private:
    Button* leave;
    Button* stay;
    QGraphicsView* dialog_view;
    QGraphicsScene* dialog_scene;
    QGraphicsTextItem* text;
};

#endif // QUITWINDOW_H
