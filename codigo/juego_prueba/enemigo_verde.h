#ifndef ENEMIGO_VERDE_H
#define ENEMIGO_VERDE_H

#include "enemigos.h"

class enemigo_verde : public enemigos
{
    Q_OBJECT

public:
    explicit enemigo_verde(QGraphicsItem *jugador, QObject *parent = nullptr);


public slots:
    void mover() override;  // Personaliza el movimiento
private:
    QGraphicsItem *jugador;
    bool impulso_activo;
    qreal velocidad_normal;
    qreal velocidad_impulso;
    int tiempo_impulso_ms;
    QTimer *temporizador_impulso;


};

#endif // ENEMIGO_VERDE_H
