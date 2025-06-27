
// fondo.h
#ifndef FONDO_H
#define FONDO_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QObject>
#include <QTimer>

class Fondo : public QObject {
    Q_OBJECT
public:
    Fondo(QGraphicsScene* scene, int tiempo_limite_ms = 40000);

private:
    QGraphicsScene* scene;
    QTimer* timer;
    int tiempoTranscurrido;
    int tiempoLimite;
};

#endif // FONDO_H

