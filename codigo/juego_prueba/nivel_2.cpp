#include "nivel_2.h"
#include "esfera_azul.h"

#include <QGraphicsRectItem>
#include <QBrush>
#include <QVBoxLayout>
#include <QTimer>
#include <QDebug>
#include <QMessageBox>

nivel_2::nivel_2(QWidget *parent)
    : QWidget(parent), escena(nullptr), vista(nullptr),
    matrizLaberinto(nullptr), personaje(nullptr),
    totalEsferas(0), esferasRecolectadas(0), puedeFinalizar(false) {}

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

    // ⏱️ Temporizador para verificar recolección de esferas
    QTimer* timerRecoleccion = new QTimer(this);
    connect(timerRecoleccion, &QTimer::timeout, this, &nivel_2::verificarRecoleccion);
    timerRecoleccion->start(100);

    show();

    QTimer* verificadorFinal = new QTimer(this);
    connect(verificadorFinal, &QTimer::timeout, this, &nivel_2::verificarFinalizacion);
    verificadorFinal->start(100);  // revisa cada 100 ms

}

void nivel_2::construirMatriz() {
    int laberintoBase[filas][columnas] = {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,7,0,0,0,0,0,0,1,1,1,7,0,0,0,0,0,1,1,0,0,0,0,9,1},
        {1,0,1,1,1,1,0,0,0,0,1,0,1,1,0,0,0,0,0,0,1,1,0,0,1},
        {1,0,1,0,0,0,0,1,1,0,1,0,1,0,1,0,0,0,1,0,0,0,1,0,1},
        {1,0,1,0,1,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1},
        {1,0,1,0,1,0,1,0,0,0,0,0,0,0,1,0,1,0,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,0,1,1,1,1,1,0,1,1,1,0,1,1,1,1,1,0,1,0,1,0,1},
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

void nivel_2::construirMapa() {
    totalEsferas = 0;
    esferasRecolectadas = 0;
    QGraphicsRectItem* celdaFinal = nullptr;

    for (int y = 0; y < filas; ++y) {
        for (int x = 0; x < columnas; ++x) {
            QGraphicsRectItem* celda = new QGraphicsRectItem(x * tamanoCelda, y * tamanoCelda, tamanoCelda, tamanoCelda);

            if (matrizLaberinto[y][x] == 1)
                celda->setBrush(QBrush(Qt::darkYellow));
            else if (matrizLaberinto[y][x] == 9) {
                celda->setBrush(QBrush(Qt::blue));
                celdaFinal = celda;  // 👈 Guardamos el rectángulo final
            }
            else if (matrizLaberinto[y][x] == 7) {
                celda->setBrush(QBrush(Qt::black));  // Fondo debajo de la esfera
                Esfera_Azul* esfera = new Esfera_Azul();
                esfera->setPos(x * tamanoCelda, y * tamanoCelda);
                escena->addItem(esfera);
                totalEsferas++;
            }
            else
                celda->setBrush(QBrush(Qt::black));

            celda->setPen(Qt::NoPen);
            escena->addItem(celda);
        }
    }
    this->celdaFinal = celdaFinal;
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
                    celdaFinal->setBrush(QBrush(Qt::white)); // o Qt::yellow para dorado
                    celdaFinal->setGraphicsEffect(nullptr);  // En caso de que quieras aplicar un brillo, se puede hacer con QGraphicsColorizeEffect
                }
                brilloTimer = new QTimer(this);
                connect(brilloTimer, &QTimer::timeout, this, [=]() {
                    if (!celdaFinal) return;
                    QColor color = estadoBrillo ? Qt::yellow : Qt::white;
                    celdaFinal->setBrush(QBrush(color));
                    estadoBrillo = !estadoBrillo;
                });
                brilloTimer->start(500);  // cambia de color cada 0.5 segundos

                qDebug() << "¡Ahora puedes ir al punto final!";

            }

            break;
        }
    }
}

void nivel_2::verificarFinalizacion() {
    if (!puedeFinalizar || !personaje) return;

    int fila = personaje->y() / tamanoCelda;
    int columna = personaje->x() / tamanoCelda;

    if (matrizLaberinto[fila][columna] == 9) {
        QMessageBox::information(this, "Juego Terminado", "🎉 ¡Felicidades! Has completado el juego.");
        close();  // o qApp->quit(); si deseas cerrar todo
    }
}
