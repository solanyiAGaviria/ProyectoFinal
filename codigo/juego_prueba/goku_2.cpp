#include "goku_2.h"
#include <QPixmap>
#include <QDebug>
#include <QTransform>

goku_2::goku_2(int **matriz, int filas, int columnas, int tamano_celda)
    : matriz_laberinto(matriz), filas(filas), columnas(columnas), tamano(tamano_celda),
    velocidad_y(0), en_el_aire(false), puede_saltar(true), animacion_cuadro(0),
    direccion_izquierda(false), direccionX(0)
{
    hoja_sprite.load(":/spriet/goku_2 .png");
    ancho_sprite = hoja_sprite.width() / 9.4;
    alto_sprite = hoja_sprite.height() / 3;

    setPixmap(hoja_sprite.copy(ancho_sprite * 1, alto_sprite * 2, ancho_sprite, alto_sprite).scaled(tamano, tamano));
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();

    temporizador_salto = new QTimer(this);
    connect(temporizador_salto, &QTimer::timeout, this, &goku_2::saltar);

    // Timer para caída automática si no hay piso
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

    // Timer para movimiento suave horizontal
    temporizadorMovimiento = new QTimer(this);
    connect(temporizadorMovimiento, &QTimer::timeout, this, [=]() {
        if (direccionX != 0) {
            int nuevaX = x() + direccionX;
            if (!colision(nuevaX, y()))
                setX(nuevaX);
            actualizarAnimacion("correr");
        }
    });
    temporizadorMovimiento->start(20); // más bajo = más fluido
}

void goku_2::keyPressEvent(QKeyEvent *evento) {
    teclas_presionadas.insert(evento->key());

    if (evento->key() == Qt::Key_A) {
        direccionX = -3;
        direccion_izquierda = true;
    } else if (evento->key() == Qt::Key_D) {
        direccionX = 3;
        direccion_izquierda = false;
    }

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

    if ((evento->key() == Qt::Key_A && direccionX < 0) ||
        (evento->key() == Qt::Key_D && direccionX > 0)) {
        direccionX = 0;
        actualizarAnimacion("idle");
    }
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
    int margen = tamano * 0.25;

    int izquierda = nuevaX + margen;
    int derecha = nuevaX + tamano - 1 - margen;
    int arriba = nuevaY + margen;
    int abajo = nuevaY + tamano - 1 - margen;

    int col_izq = izquierda / tamano;
    int col_der = derecha / tamano;
    int fila_arriba = arriba / tamano;
    int fila_abajo = abajo / tamano;

    if (col_izq < 0 || col_der >= columnas || fila_arriba < 0 || fila_abajo >= filas)
        return true;

    return (
        matriz_laberinto[fila_arriba][col_izq] == 1 ||
        matriz_laberinto[fila_arriba][col_der] == 1 ||
        matriz_laberinto[fila_abajo][col_izq] == 1 ||
        matriz_laberinto[fila_abajo][col_der] == 1
        );
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
    } else if (accion == "idle") {
        columna = 1;
    }

    QPixmap sprite = hoja_sprite.copy(columna * ancho_sprite, fila * alto_sprite, ancho_sprite, alto_sprite)
                         .scaled(tamano, tamano);

    if (direccion_izquierda)
        sprite = sprite.transformed(QTransform().scale(-1, 1));

    setPixmap(sprite);
}
