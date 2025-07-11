#include "esfera_azul.h"

Esfera_Azul::Esfera_Azul(double tamano) {
    setRect(0, 0, tamano, tamano);
    setBrush(QBrush(Qt::blue));
    setZValue(1);  // Asegura que esté encima del fondo
}
