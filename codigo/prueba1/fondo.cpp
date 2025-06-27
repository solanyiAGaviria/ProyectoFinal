// fondo.cpp
#include "fondo.h"
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QDebug>

Fondo::Fondo(QGraphicsScene* scene, int tiempo_limite_ms)
    : scene(scene), tiempoTranscurrido(0), tiempoLimite(tiempo_limite_ms) {

    QPixmap fondoImg(":/fondo/torre_super_alta.jpg");
    if (fondoImg.isNull()) {
        qDebug() << "Error: No se pudo cargar la imagen de fondo.";
        return;
    }

    // Calcular cuántas repeticiones necesitamos para cubrir 40 segundos de subida
    int velocidadPixelesPorFrame = 10;         // ejemplo de velocidad
    int fps = 33;                               // asumiendo 30 ms por frame
    int totalPixeles = (tiempoLimite / 1000.0) * (1000.0 / fps) * velocidadPixelesPorFrame;

    int altoEscena = scene->height();
    int altoFondo = fondoImg.height();
    int repeticiones = totalPixeles / altoFondo + 2; // un poco más por seguridad

    // Añadir varias copias del fondo en la escena
    for (int i = 0; i < repeticiones; ++i) {
        QGraphicsPixmapItem* capa = new QGraphicsPixmapItem(fondoImg.scaled(scene->width(), fondoImg.height(), Qt::IgnoreAspectRatio));
        capa->setPos(0, -i * fondoImg.height()); // hacia arriba
        capa->setZValue(-1);
        scene->addItem(capa);
    }

    // (Opcional) Iniciar temporizador si quieres hacer algo al final de los 40 segundos
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [=]() {
        tiempoTranscurrido += 30;
        if (tiempoTranscurrido >= tiempoLimite) {
            timer->stop();
            qDebug() << "Tiempo cumplido. Fin del ascenso.";
            // Aquí puedes lanzar una señal para decir "ganó", "pasó de nivel", etc.
        }
    });
    timer->start(30);
}



