#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMediaPlayer>
#include <QLineEdit>
#include <QKeyEvent>
#include <QProgressBar>
#include "button.h"
#include "map.h"
#include "player.h"

enum difficulty
{easy,medium,hard};

enum path_type
{bck,ico,tl};

class Map;
class Player;
class Menu;

class Game: public QWidget
{
    Q_OBJECT
public:
    Game();
    ~Game();

    void drawInterface();
    void create_player(QString name);
    void createMap(int lvl, int dif);
    void displayMenu();
    void setInterface();
    void newGame();
    void modifyHpBar(bool upgrade);
    void modifyReloadBar(int time);
    void modifyAmmo();
    void modifyAmmoFrame();
    void modifyUTracks(int number);
    void modifyUEngine(int number);
    void modifyUArmor();
    void endGame(bool win);
    QString getPath(int path_type);

private slots:
    void set_baron();
    void set_kabaczek();
    void set_fiolet();
    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent *event);

private:

    Menu* menu = nullptr;
    Player* player = nullptr;
    Map* map = nullptr;

    QLineEdit* username = nullptr;

    QGraphicsView* init_view = nullptr;
    QGraphicsView* game_interface = nullptr;
    QGraphicsView* map_view = nullptr;

    QGraphicsScene* init_scene = nullptr;
    QGraphicsScene* interface_scene = nullptr;

    Button* red_baron = nullptr;
    Button* kabaczek = nullptr;
    Button* fiolet = nullptr;

    QGraphicsTextItem *text = nullptr;
    QGraphicsTextItem *player_name = nullptr;

    QGraphicsTextItem* APNum = nullptr;
    QGraphicsTextItem* HENum = nullptr;
    QGraphicsTextItem* UTrack = nullptr;
    QGraphicsTextItem* UEngine = nullptr;
    QGraphicsTextItem* UArmor = nullptr;

    QGraphicsPixmapItem* frame = nullptr;

    QProgressBar* hp_bar = nullptr;
    QProgressBar* reload_bar = nullptr;

    int diffic = 0;

    QString bckg_path = ":/img/img/background_02.png";
    QString icon_path = ":/img/img/icon.png";
    QString win_title = "CZOLGI WARS";
    QString interface_background = ":/img/img/interface_bckg.jpg";
    QString AP_icon = ":/img/img/APShell.png";
    QString HE_icon = ":/img/img/HEShell.png";
    QString ramka = ":/img/img/ramka.png";

protected:
    int win_width = 1360;
    int win_height = 800;
};

#endif // GAME_H
