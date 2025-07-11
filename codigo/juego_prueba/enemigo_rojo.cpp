#include "enemigo_rojo.h"
#include <QTimer>
#include <QGraphicsScene>
#include <cmath>
#include <QPixmap>

enemigo_rojo::enemigo_rojo(QObject *parent)
    : enemigos(parent)
{
    setPixmap(QPixmap(":/spriet/rojo.png").scaled(60, 60));

    x_inicial = x();
    velocidad_y = 4;
    amplitud = 150.0;
    frecuencia = 0.01;

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &enemigo_rojo::mover);
    timer->start(10);
}
void enemigo_rojo::mover()
{
    qreal y_actual = y() + velocidad_y;
    qreal x_nuevo = x_inicial + amplitud * sin(frecuencia * y_actual);

    setPos(x_nuevo, y_actual);

    if (y_actual > 780) {
        scene()->removeItem(this);
        delete this;
    }
}
