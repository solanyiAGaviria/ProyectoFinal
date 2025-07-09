#include "enemigo_rojo.h"
#include <QTimer>
#include <QBrush>
#include <QGraphicsScene>
#include <cmath>
enemigo_rojo::enemigo_rojo(QObject *parent)
    : enemigos(parent)
{
    setBrush(Qt::red);

    x_inicial = x();       // Se define después de ser añadido a la escena
    velocidad_y = 4;
    amplitud = 150.0;       // Cuánto se mueve hacia los lados
    frecuencia = 0.01;     // Qué tan rápido oscila

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
