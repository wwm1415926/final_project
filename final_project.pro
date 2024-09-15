QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    choosescene.cpp \
    game.cpp \
    helpscene.cpp \
    main.cpp \
    mainscene.cpp \
    myRole.cpp \
    mybullet.cpp \
    mypushbutton.cpp \
    playscene.cpp \
    role_A.cpp \
    role_B.cpp \
    role_C.cpp \
    role_D.cpp \
    role_E.cpp \
    role_G.cpp \
    storescene.cpp

HEADERS += \
    choosescene.h \
    game.h \
    grid.h \
    helpscene.h \
    mainscene.h \
    myRole.h \
    mybullet.h \
    mypushbutton.h \
    playscene.h \
    role_A.h \
    role_B.h \
    role_C.h \
    role_D.h \
    role_E.h \
    role_G.h \
    storescene.h

FORMS += \
    mainscene.ui

TRANSLATIONS += \
    final_project_en_150.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
