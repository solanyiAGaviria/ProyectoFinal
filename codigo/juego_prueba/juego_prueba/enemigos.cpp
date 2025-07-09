#include "enemigos.h"
#include <QGraphicsScene>
#include <QDebug>
#include <cstdlib>

enemigos::enemigos(QObject *parent)
    : QObject(parent)
{
    // Posición aleatoria en la parte superior
    int random_number = rand() % 644;
    setPos(180 + random_number, -11824);

    // Forma por defecto
    setRect(0, 0, 100, 100);
}

enemigos::~enemigos()
{
    qDebug() << "enemigo destruido";
}

void enemigos::mover()
{
    setPos(x(), y() + 2);

    if (pos().y() > 780) {
        scene()->removeItem(this);
        delete this;
    }
}

