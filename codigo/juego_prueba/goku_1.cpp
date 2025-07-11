#include "goku_1.h"
#include <QTransform>
#include <QGraphicsScene>
#include "bala.h"

goku_1::goku_1() : frame(0), direccion_izquierda(false) {
    spriteSheet.load(":/spriet/goku.png");

    // Define los recortes del sprite
    recortes[0] = QRect(0, 0, 41, 61);
    recortes[1] = QRect(45, 0, 41, 61);
    recortes[2] = QRect(90, 0, 41, 61);

    setPixmap(spriteSheet.copy(recortes[0]).scaled(76, 96));
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();
    setZValue(1);
}

void goku_1::keyPressEvent(QKeyEvent *event) {
    int dx = 0;
    int dy = 0;

    if (event->key() == Qt::Key_W && pos().y() > -11520) {
        dy = -10;
    } else if (event->key() == Qt::Key_S && pos().y() - 700) {
        dy = 10;
    } else if (event->key() == Qt::Key_A && pos().x() > 180) {
        dx = -10;
        direccion_izquierda = true;
    } else if (event->key() == Qt::Key_D && pos().x() < 800) {
        dx = 10;
        direccion_izquierda = false;
    }

    if (dx != 0 || dy != 0) {
        frame = (frame + 1) % 3;
        QPixmap sprite = spriteSheet.copy(recortes[frame]).scaled(76, 96);
        if (direccion_izquierda)
            sprite = sprite.transformed(QTransform().scale(-1, 1));
        setPixmap(sprite);

        setPos(x() + dx, y() + dy);
        emit meMuevo(this);
    }
}
