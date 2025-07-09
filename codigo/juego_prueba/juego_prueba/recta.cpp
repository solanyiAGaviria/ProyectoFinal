#include "recta.h"
#include<QKeyEvent>
#include<QGraphicsScene>
#include "bala.h"
#include <QDebug>


recta::recta()
{
    // Puedes dejarlo vacío o inicializar algo
}

void recta::keyPressEvent(QKeyEvent *event){
    if (event->key() == Qt::Key_W) {if(pos().y()>-11520){setPos(x(),y()-10);}}
    else if (event->key() == Qt::Key_S) {if(pos().y()-700)setPos(x(),y()+10);}
    else if (event->key() == Qt::Key_A) {if(pos().x()>180){setPos(x()-10,y());}}
    else if (event->key() == Qt::Key_D) {if(pos().x()<800){setPos(x()+10,y());}}
    else if (event->key() == Qt::Key_Space)
    {//creacion de bala
        bala * dispara = new bala();
        dispara->setPos(x(),y());
        qDebug() <<"bala creada ";
        scene()->addItem(dispara);
    }
    emit meMuevo(this); // emites una señal con tu puntero
}


/*
void recta::spawn(){
    // creacion de enemigos
    enemigos* enemy = new enemigos;
    scene()->addItem(enemy);
}
*/
