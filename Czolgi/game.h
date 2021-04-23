#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QGraphicsView>

class Menu : public QGraphicsView
{
    Q_OBJECT

public:
    Menu(QWidget *parent = nullptr, int w_size = 1360, int h_size = 800);

    QGraphicsScene* scene;
    QGraphicsTextItem* title;
    QGraphicsTextItem* ver_inf;

    void display_menu();

    ~Menu();
};
#endif // GAME_H
