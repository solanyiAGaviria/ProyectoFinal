QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    enemigo_azul.cpp \
    enemigo_rojo.cpp \
    enemigo_verde.cpp \
    enemigos.cpp \
    esfera_azul.cpp \
    goku_1.cpp \
    goku_2.cpp \
    main.cpp \
    mainwindow.cpp \
    nivel_1.cpp \
    nivel_2.cpp \
    paso_de_nivel.cpp \
    premio.cpp

HEADERS += \
    enemigo_azul.h \
    enemigo_rojo.h \
    enemigo_verde.h \
    enemigos.h \
    esfera_azul.h \
    goku_1.h \
    goku_2.h \
    mainwindow.h \
    nivel_1.h \
    nivel_2.h \
    paso_de_nivel.h \
    premio.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    sprites.qrc
