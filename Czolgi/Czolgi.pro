QT       += core gui \
            multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bullet.cpp \
    button.cpp \
    credits.cpp \
    enemy.cpp \
    game.cpp \
    main.cpp \
    map.cpp \
    menu.cpp \
    player.cpp \
    quitwindow.cpp

HEADERS += \
    bullet.h \
    button.h \
    credits.h \
    enemy.h \
    game.h \
    map.h \
    menu.h \
    player.h \
    quitwindow.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
