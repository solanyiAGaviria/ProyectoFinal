#ifndef ENEMIGO_ROJO_H
#define ENEMIGO_ROJO_H

#include "enemigos.h"

class enemigo_rojo : public enemigos
{
    Q_OBJECT

public:
    explicit enemigo_rojo(QObject *parent = nullptr);

public slots:
    void mover() override;

private:
    qreal x_inicial;
    int velocidad_y;
    qreal amplitud;
    qreal frecuencia;

};

#endif // ENEMIGO_ROJO_H
