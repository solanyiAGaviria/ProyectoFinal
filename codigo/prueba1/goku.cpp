// goku.cpp
#include "goku.h"

Goku::Goku() {
    spriteSheet.load(":/goku/goku.png");
    recortes[0] = QRect(0, 0, 41, 61);
    recortes[1] = QRect(45, 0, 41, 61);
    recortes[2] = QRect(90, 0, 41, 61);
    frame = 0;

    setPixmap(spriteSheet.copy(recortes[0]).scaled(76, 96));
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();
    setZValue(1);  // Para que esté encima del fondo

}

void Goku::keyPressEvent(QKeyEvent* event) {
    int dx = 0;
    int dy = 0;

    if (event->key() == Qt::Key_W) dy = -tamano_pantalla;
    else if (event->key() == Qt::Key_S) dy = tamano_pantalla;
    else if (event->key() == Qt::Key_A) dx = -tamano_pantalla;
    else if (event->key() == Qt::Key_D) dx = tamano_pantalla;
    else return;

    setPos(x() + dx, y() + dy);
    frame = (frame + 1) % 3;
    actualizarSprite();

    emit gokuSeMovio(y());  // Emitir posición actual para mover la vista
}

void Goku::actualizarSprite() {
    QPixmap sprite = spriteSheet.copy(recortes[frame]);
    setPixmap(sprite.scaled(76, 96));
}


