#include "bala.h"
#include <QTimer>
#include<QGraphicsScene>
#include<QDebug>
#include<QList>
#include"enemigos.h"
bala::bala(){
    //creacion de bala
    setRect(0,0,7,15);

    //connect
    QTimer * tiempo = new QTimer(this);
    connect(tiempo,SIGNAL(timeout()),this,SLOT(mover()));

    tiempo->start(5);
}

bala::~bala()
{

}

void bala::mover() {
    // Colisiones
    QList<QGraphicsItem *> colisionados = collidingItems();

    for (int i = 0; i < colisionados.size(); ++i) {
        if (typeid(*colisionados[i]) == typeid(enemigos)) {
            // Remover de la escena
            scene()->removeItem(colisionados[i]);
            scene()->removeItem(this);

            // Eliminación de memoria
            delete colisionados[i];
            delete this;

            return; // Salimos para evitar usar this eliminado
        }
    }

    // Movimiento
    setPos(x(), y() - 2);

    // Si sale de la pantalla, eliminar la bala
    if (pos().y() < -11520) {
        scene()->removeItem(this);
        delete this;
        qDebug() << "bala eliminada";
    }
}
