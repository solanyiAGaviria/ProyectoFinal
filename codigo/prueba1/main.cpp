/*#include <QApplication>
#include "juego.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Juego juego;
    juego.show();
    return app.exec();
}*/
/*
#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include "goku.h"
#include "fondo.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // 1. Crear escena
    QGraphicsScene* scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, 400, 600);  // ancho x alto

    // 2. Crear vista y conectarla con la escena
    QGraphicsView* view = new QGraphicsView(scene);
    view->setFixedSize(400, 600);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // 3. Crear y agregar fondo repetible
    Fondo* fondo = new Fondo(scene);         // ⬅️ Clase Fondo que te pasé
    scene->addItem(fondo);

    // 4. Crear y agregar personaje Goku
    Goku* goku = new Goku();
    goku->setPos(180, 400); // posición inicial en la escena
    scene->addItem(goku);

    // 5. Mostrar vista
    view->show();

    return app.exec();
}*/
#include <QApplication>
#include "juego.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Juego* juego = new Juego();
    juego->show();

    return app.exec();
}


