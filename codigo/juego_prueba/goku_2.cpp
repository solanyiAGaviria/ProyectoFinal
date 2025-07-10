#include "goku_2.h"
#include <QPixmap>
#include <QDebug>
#include <QTransform>

goku_2::goku_2(int **matriz, int filas, int columnas, int tamano_celda)
    : matriz_laberinto(matriz), filas(filas), columnas(columnas), tamano(tamano_celda),
    velocidad_y(0), en_el_aire(false), puede_saltar(true), animacion_cuadro(0), direccion_izquierda(false)
{
    hoja_sprite.load(":/spriet/goku_2 .png");
    ancho_sprite = hoja_sprite.width() / 9.5;
    alto_sprite = hoja_sprite.height() / 3;

    setPixmap(hoja_sprite.copy(ancho_sprite * 1, alto_sprite * 2, ancho_sprite, alto_sprite).scaled(tamano, tamano));
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();

    temporizador_salto = new QTimer(this);
    connect(temporizador_salto, &QTimer::timeout, this, &goku_2::saltar);

    QTimer* verificadorCaida = new QTimer(this);
    connect(verificadorCaida, &QTimer::timeout, this, [=]() {
        if (!en_el_aire && !hayPisoDebajo()) {
            velocidad_y = 1;
            en_el_aire = true;
            puede_saltar = false;
            temporizador_salto->start(30);
        }
    });
    verificadorCaida->start(50);
}

void goku_2::keyPressEvent(QKeyEvent *evento) {
    teclas_presionadas.insert(evento->key());

    int dx = 0;
    int dy = 0;

    if (evento->key() == Qt::Key_A) {
        dx = -tamano;
        direccion_izquierda = true;
        actualizarAnimacion("correr");
    } else if (evento->key() == Qt::Key_D) {
        dx = tamano;
        direccion_izquierda = false;
        actualizarAnimacion("correr");
    } else if (evento->key() == Qt::Key_S) {
        dy = tamano;
    }

    int nuevaX = x() + dx;
    int nuevaY = y() + dy;
    if (!colision(nuevaX, nuevaY))
        setPos(nuevaX, nuevaY);

    if (evento->key() == Qt::Key_W && puede_saltar) {
        velocidad_y = -12;
        en_el_aire = true;
        puede_saltar = false;
        actualizarAnimacion("saltar");
        temporizador_salto->start(30);
    }
}

void goku_2::keyReleaseEvent(QKeyEvent *evento) {
    teclas_presionadas.remove(evento->key());
}

void goku_2::saltar() {
    velocidad_y += 1;
    int nuevaY = y() + velocidad_y;

    if (!colision(x(), nuevaY)) {
        setY(nuevaY);
        actualizarAnimacion("en_el_aire");
    } else {
        int fila_actual = y() / tamano;
        setY(fila_actual * tamano);

        velocidad_y = 0;
        en_el_aire = false;
        puede_saltar = true;
        temporizador_salto->stop();
        actualizarAnimacion("correr");
    }
}

bool goku_2::colision(int nuevaX, int nuevaY) {
    int columna = nuevaX / tamano;
    int fila = nuevaY / tamano;

    if (fila < 0 || fila >= filas || columna < 0 || columna >= columnas)
        return true;

    return matriz_laberinto[fila][columna] == 1;
}

bool goku_2::hayPisoDebajo() {
    int fila = (y() + tamano + 1) / tamano;
    int columna = x() / tamano;

    if (fila >= filas)
        return false;

    return matriz_laberinto[fila][columna] == 1;
}

void goku_2::actualizarAnimacion(QString accion) {
    int fila = 1;
    int columna = 2;

    if (accion == "correr") {
        animacion_cuadro = (animacion_cuadro + 1) % 2;
        columna = 2 + animacion_cuadro;
    } else if (accion == "saltar") {
        columna = 4;
    } else if (accion == "en_el_aire") {
        columna = 5;
    } else if (accion == "caer") {
        columna = 6;
    }

    QPixmap sprite = hoja_sprite.copy(columna * ancho_sprite, fila * alto_sprite, ancho_sprite, alto_sprite)
                         .scaled(tamano, tamano);

    if (direccion_izquierda)
        sprite = sprite.transformed(QTransform().scale(-1, 1));

    setPixmap(sprite);
}
