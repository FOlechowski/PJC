#ifndef MENU_H
#define MENU_H

#include <QGraphicsView>

class Menu : public QGraphicsView
{
    Q_OBJECT

public:
    Menu(QWidget *parent = nullptr, int w_size = 1360, int h_size = 800);

    void display_menu();

    ~Menu();

public slots:
    void quit_ask();

private:
    QGraphicsScene* scene;
    QGraphicsTextItem* title;
    QGraphicsTextItem* ver_inf;
    QDialog* quit;
    QGraphicsView* quit_view;
    QGraphicsScene* quit_scene;
};
#endif // MENU_H
