#ifndef NIVEL_1_H
#define NIVEL_1_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include "goku_1.h"

class nivel_1 : public QObject
{
    Q_OBJECT

public:
    nivel_1();
    void ver();
    bool gameOverMostrado;

private:
    void spawn();
    void verificarColisiones();
    void mostrarGameOver();
    void reiniciarNivel();
    bool jugadorAturdido = false;

    QGraphicsScene *nivelScene;
    QGraphicsView *vista;
    goku_1 *jugador;

    QTimer *timerSpawn;
    QTimer *timerColision;
};

#endif // NIVEL_1_H
