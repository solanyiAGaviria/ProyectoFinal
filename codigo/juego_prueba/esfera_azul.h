#ifndef ESFERA_AZUL_H
#define ESFERA_AZUL_H

#include <QGraphicsEllipseItem>
#include <QObject>
#include <QBrush>

class Esfera_Azul : public QObject, public QGraphicsEllipseItem {
    Q_OBJECT

public:
    Esfera_Azul(double tamano = 16);  // constructor con tamaño
};

#endif // ESFERAAZUL_H
