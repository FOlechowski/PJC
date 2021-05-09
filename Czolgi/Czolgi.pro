QT       += core gui \
            multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    boss.cpp \
    bullet.cpp \
    button.cpp \
    destroyer.cpp \
    enemy.cpp \
    explosivebullet.cpp \
    game.cpp \
    heavy.cpp \
    light.cpp \
    main.cpp \
    map.cpp \
    medium.cpp \
    menu.cpp \
    obstacles.cpp \
    player.cpp \
    tank.cpp

HEADERS += \
    boss.h \
    bullet.h \
    button.h \
    destroyer.h \
    enemy.h \
    explosivebullet.h \
    game.h \
    heavy.h \
    light.h \
    map.h \
    medium.h \
    menu.h \
    obstacles.h \
    player.h \
    tank.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
