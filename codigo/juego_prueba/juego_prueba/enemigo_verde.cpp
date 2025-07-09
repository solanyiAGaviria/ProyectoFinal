#include "enemigo_verde.h"
#include <QTimer>
#include <QBrush>
#include <QGraphicsScene>
enemigo_verde::enemigo_verde(QGraphicsItem *jugador, QObject *parent)
    : enemigos(parent), jugador(jugador), impulso_activo(false)
{
    setBrush(Qt::green);

    velocidad_normal = 1;
    velocidad_impulso = 6;
    tiempo_impulso_ms = 3000;

    temporizador_impulso = new QTimer(this);
    temporizador_impulso->setSingleShot(true);
    connect(temporizador_impulso, &QTimer::timeout, [=]() {
        impulso_activo = false;
    });

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &enemigo_verde::mover);
    timer->start(10);
}

void enemigo_verde::mover()
{
    if (!jugador) return;

    qreal dx = jugador->x() - x();
    qreal dy = jugador->y() - y();
    qreal distancia = std::sqrt(dx*dx + dy*dy);

    // Si está cerca y aún no ha activado impulso
    if (distancia < 250 && !impulso_activo) {
        impulso_activo = true;
        temporizador_impulso->start(tiempo_impulso_ms); // después de 3s, se desactiva
    }

    // Mover según el estado
    if (impulso_activo) {
        setY(y() + velocidad_impulso);
    } else {
        setY(y() + velocidad_normal);
    }

    if (y() > 780) {
        scene()->removeItem(this);
        delete this;
    }
}
