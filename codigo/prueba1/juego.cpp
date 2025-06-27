/*#include "juego.h"

Juego::Juego(QWidget *parent) : QGraphicsView(parent) {
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 400, 600);
    setScene(scene);

    goku = new Goku();
    scene->addItem(goku);
    goku->setPos(200, 500);  // posición inicial

    setFixedSize(400, 600);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFocus();
}*/
// juego.cpp
/*#include "juego.h"
#include <QScrollBar>

Juego::Juego(QWidget *parent) : QGraphicsView(parent) {
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, -1000, 400, 1600); // Espacio más alto hacia arriba
    setScene(scene);

    Fondo* fondo = new Fondo(scene);
    scene->addItem(fondo);

    goku = new Goku();
    scene->addItem(goku);
    goku->setPos(200, 500);  // posición inicial
    connect(goku, &Goku::gokuSeMovio, this, &Juego::seguirAGoku);

    setFixedSize(400, 600);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFocus();
}

void Juego::seguirAGoku(int yGoku) {
    // Centrar la vista en Goku cuando sube
    centerOn(goku);
}*/

#include "juego.h"
#include "fondo.h"

Juego::Juego(QWidget *parent) : QGraphicsView(parent) {
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, -3000, 400, 4000);  // Espacio vertical grande
    setScene(scene);

    Fondo* fondo = new Fondo(scene, 40000);  // Repetir fondo para 40 segundos
    goku = new Goku();
    scene->addItem(goku);
    goku->setPos(200, 500);  // posición inicial
    connect(goku, &Goku::gokuSeMovio, this, &Juego::seguirAGoku);

    setFixedSize(400, 600);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFocus();
}
#include "juego.h"

void Juego::seguirAGoku(int yGoku) {
    centerOn(goku);  // o podrías usar centerOn(0, yGoku) si quieres solo vertical
}

