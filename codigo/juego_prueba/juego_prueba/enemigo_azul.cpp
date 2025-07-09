#include "enemigo_azul.h"
#include <QTimer>
#include <QBrush>
#include <QGraphicsScene>
#include <cmath>

enemigo_azul::enemigo_azul(QObject *parent)
    : enemigos(parent)
{
    setBrush(Qt::blue);

    // Posición inicial del centro del círculo
    centroX = x(); // Se actualizará luego si se define setPos
    centroY = y();

    radio = 200;          // radio del movimiento circular
    angulo = 0;          // ángulo inicial en radianes
    avance = 0;          // cuánto ha descendido el enemigo

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &enemigo_azul::mover);
    timer->start(10);
}
void enemigo_azul::mover()
{
    angulo += 0.008;     // Aumenta el ángulo para que gire y esto determina la velocidad de giro
    avance += 1;     // Descenso progresivo (velocidad vertical)

    qreal x_actual = centroX + radio * cos(angulo);
    qreal y_actual = centroY + radio * sin(angulo) + avance;

    setPos(x_actual, y_actual);

    if (y_actual > 780) {
        scene()->removeItem(this);
        delete this;
    }
}
