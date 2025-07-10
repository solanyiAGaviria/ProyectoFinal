#include "enemigo_azul.h"
#include <QTimer>
#include <QGraphicsScene>
#include <cmath>
#include <QPixmap>

enemigo_azul::enemigo_azul(QObject *parent)
    : enemigos(parent)
{
    setPixmap(QPixmap(":/spriet/azul.png").scaled(60, 60)); // Ajusta tamaño e imagen

    centroX = x();
    centroY = y();
    radio = 200;
    angulo = 0;
    avance = 0;

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
