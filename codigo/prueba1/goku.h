/*#ifndef GOKU_H
#define GOKU_H

#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QPixmap>

#define tamano_pantalla 64  // Ajusta si quieres un tamaño diferente en pantalla

class Goku : public QGraphicsPixmapItem {
public:
    Goku();
    void keyPressEvent(QKeyEvent* event);

private:
    QPixmap spriteSheet;
    int frame;
    QRect recortes[3];  // Regiones del sprite para cada animación
    void actualizarSprite();
};

#endif // GOKU_H*/
// goku.h
#ifndef GOKU_H
#define GOKU_H

#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QPixmap>
#include <QObject>

#define tamano_pantalla 64

class Goku : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Goku();
    void keyPressEvent(QKeyEvent* event);

signals:
    void gokuSeMovio(int y);

private:
    QPixmap spriteSheet;
    int frame;
    QRect recortes[3];
    void actualizarSprite();
};

#endif // GOKU_H


