#include "nivel_2.h"
#include "esfera_azul.h"
#include "goku_2.h"

#include <QGraphicsRectItem>
#include <QBrush>
#include <QVBoxLayout>
#include <QTimer>
#include <QDebug>
#include <QLabel>
#include <QFont>
#include <QDialog>
#include <QPushButton>

nivel_2::nivel_2(QWidget *parent) : QWidget(parent), escena(nullptr), vista(nullptr),
    matrizLaberinto(nullptr), celdaFinal(nullptr), personaje(nullptr), puedeFinalizar(false),
    totalEsferas(0), esferasRecolectadas(0) {}

void nivel_2::ver() {
    escena = new QGraphicsScene(this);
    vista = new QGraphicsView(escena, this);
    vista->setFixedSize(columnas * tamanoCelda, filas * tamanoCelda);
    escena->setSceneRect(0, 0, columnas * tamanoCelda, filas * tamanoCelda);
    setFixedSize(vista->size());
    setWindowTitle("Nivel 2");
    setLayout(new QVBoxLayout);
    layout()->addWidget(vista);

    construirMatriz();
    construirMapa();

    personaje = new goku_2(matrizLaberinto, filas, columnas, tamanoCelda);
    escena->addItem(personaje);
    personaje->setPos(1 * tamanoCelda, 17 * tamanoCelda);
    personaje->setFocus();

    QTimer* verificador = new QTimer(this);
    connect(verificador, &QTimer::timeout, this, &nivel_2::verificarRecoleccion);
    verificador->start(100);

    QTimer* verificadorTP = new QTimer(this);
    connect(verificadorTP, &QTimer::timeout, this, &nivel_2::verificarTeletransportador);
    verificadorTP->start(100);

    show();
}

void nivel_2::construirMapa() {
    totalEsferas = 0;
    esferasRecolectadas = 0;

    // Transportadores invisibles: entradas y salidas corregidas
    teleEntradas = { QPoint(4, 2), QPoint(10, 1), QPoint(5, 12) };
    teleSalidas  = { QPoint(22, 2), QPoint(6, 13), QPoint(17, 8) };


    for (int y = 0; y < filas; ++y) {
        for (int x = 0; x < columnas; ++x) {
            QGraphicsRectItem* celda = new QGraphicsRectItem(x * tamanoCelda, y * tamanoCelda, tamanoCelda, tamanoCelda);

            if (matrizLaberinto[y][x] == 1) {
                celda->setBrush(QBrush(QColor(97, 132, 227))); // Muros
            }
            else if (matrizLaberinto[y][x] == 9) {
                celda->setBrush(QBrush(QColor(106, 255, 242))); // Meta
                celdaFinal = celda;
            }
            else if (matrizLaberinto[y][x] == 7) {
                celda->setBrush(QBrush(Qt::black)); // Fondo + esfera
                Esfera_Azul* esfera = new Esfera_Azul();
                esfera->setPos(x * tamanoCelda + tamanoCelda / 4, y * tamanoCelda + tamanoCelda / 4);
                escena->addItem(esfera);
                totalEsferas++;
            }
            else {
                celda->setBrush(QBrush(Qt::black)); // Fondo normal
            }

            celda->setPen(Qt::NoPen);
            escena->addItem(celda);
        }
    }
}


void nivel_2::verificarTeletransportador() {
    if (!personaje) return;

    int xJugador = personaje->x() / tamanoCelda;
    int yJugador = personaje->y() / tamanoCelda;

    for (int i = 0; i < teleEntradas.size(); ++i) {
        QPoint entrada = teleEntradas[i];
        if (entrada.x() == xJugador && entrada.y() == yJugador) {
            QPoint destino = teleSalidas[i];
            personaje->setPos(destino.x() * tamanoCelda, destino.y() * tamanoCelda);
            qDebug() << "Teletransportado de (" << entrada << ") a (" << destino << ")";
            break;
        }
    }
}


void nivel_2::construirMatriz() {
    int laberintoBase[filas][columnas] = {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,1,1,1,7,0,0,0,0,0,0,0,0,0,0,0,9,1},
        {1,0,1,1,0,0,0,0,0,0,1,0,1,1,0,0,0,0,0,0,1,1,0,0,1},
        {1,0,1,0,1,0,0,1,1,0,1,0,1,0,1,0,0,0,1,0,0,0,1,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1},
        {1,0,1,0,1,0,1,0,0,0,0,0,0,0,1,0,1,0,1,1,1,1,1,1,1},
        {1,7,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,0,1,1,1,1,1,0,1,1,1,0,1,1,1,1,1,0,1,0,1,0,1},
        {1,7,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,0,0,1},
        {1,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,7,0,0,0,1,0,0,1},
        {1,0,1,0,1,1,0,0,1,1,1,1,1,1,1,0,0,1,1,1,0,0,1,0,1},
        {1,7,0,7,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1},
        {1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };

    matrizLaberinto = new int*[filas];
    for (int i = 0; i < filas; ++i) {
        matrizLaberinto[i] = new int[columnas];
        for (int j = 0; j < columnas; ++j)
            matrizLaberinto[i][j] = laberintoBase[i][j];
    }
}

void nivel_2::verificarRecoleccion() {
    if (!personaje) return;

    QList<QGraphicsItem*> colisiones = personaje->collidingItems();

    for (QGraphicsItem* item : colisiones) {
        Esfera_Azul* esfera = dynamic_cast<Esfera_Azul*>(item);
        if (esfera) {
            escena->removeItem(esfera);
            delete esfera;
            esferasRecolectadas++;

            qDebug() << "Esferas recolectadas: " << esferasRecolectadas;

            if (esferasRecolectadas >= totalEsferas) {
                puedeFinalizar = true;

                if (celdaFinal) {
                    celdaFinal->setBrush(QBrush(QColor(255, 255, 240)));
                    QTimer::singleShot(1000, this, [=]() {
                        celdaFinal->setBrush(QBrush(QColor(255, 255, 100)));
                    });
                }
            }

            break;
        }
    }

    if (puedeFinalizar) {
        int xJugador = personaje->x() / tamanoCelda;
        int yJugador = personaje->y() / tamanoCelda;
        if (matrizLaberinto[yJugador][xJugador] == 9) {
            mostrarMensajeFinal();
        }
    }
}

void nivel_2::mostrarMensajeFinal() {
    QDialog* ventana = new QDialog(this);
    ventana->setFixedSize(250, 250);
    ventana->setStyleSheet("background-color: black;");

    QLabel* texto = new QLabel("\u00a1Juego Terminado!", ventana);
    texto->setAlignment(Qt::AlignCenter);
    texto->setStyleSheet("color: gold;");
    texto->setFont(QFont("Arial Rounded MT Bold", 18, QFont::Bold));
    texto->setGeometry(0, 90, 250, 40);

    QTimer::singleShot(3000, ventana, [=]() {
        ventana->accept();
        close();
    });

    ventana->exec();
}

