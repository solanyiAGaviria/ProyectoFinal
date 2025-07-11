#ifndef ENEMIGO_AZUL_H
#define ENEMIGO_AZUL_H

#include "enemigos.h"

class enemigo_azul : public enemigos
{
    Q_OBJECT

public:
    explicit enemigo_azul(QObject *parent = nullptr);

public slots:
    void mover() override;

private:
    qreal centroX;
    qreal centroY;
    qreal radio;
    qreal angulo;
    qreal avance;

};

#endif // ENEMIGO_AZUL_H
