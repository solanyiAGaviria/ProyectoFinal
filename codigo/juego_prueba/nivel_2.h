#ifndef NIVEL_2_H
#define NIVEL_2_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QList>

#include "goku_2.h"

const int filas = 20;
const int columnas = 25;
const int tamanoCelda = 30;

class nivel_2 : public QWidget {
    Q_OBJECT

public:
    explicit nivel_2(QWidget *parent = nullptr);
    void ver();

private:
    QGraphicsScene* escena;
    QGraphicsView* vista;
    int** matrizLaberinto;
    void verificarFinalizacion();
    QGraphicsRectItem* celdaFinal = nullptr;
    QTimer* brilloTimer = nullptr;
    bool estadoBrillo = false;
    goku_2* personaje;

    int totalEsferas;
    int esferasRecolectadas;
    bool puedeFinalizar;

    bool enPuntoFinal();
    void mostrarMensajeFinal();

    void construirMatriz();
    void construirMapa();
    void verificarRecoleccion();
    void verificarTeletransportador();

    QVector<QPoint> teleEntradas;
    QVector<QPoint> teleSalidas;
};

#endif // NIVEL_2_H
