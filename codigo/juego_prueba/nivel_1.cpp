#include "nivel_1.h"
#include "goku_1.h"
#include "enemigo_rojo.h"
#include "enemigo_azul.h"
#include "enemigo_verde.h"
#include "premio.h"
#include"paso_de_nivel.h"
#include "mainwindow.h"

#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QApplication>
#include <QScreen>
#include <QTimer>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QGraphicsTextItem>
#include <QDebug>
#include <cstdlib>
#include <ctime>

nivel_1::nivel_1() {
    jugador = nullptr;
    vista = nullptr;
    nivelScene = nullptr;
    timerSpawn = nullptr;
    timerColision = nullptr;
    jugadorAturdido = false;
    std::srand(std::time(nullptr));
}
void nivel_1::ver() {
    nivelScene = new QGraphicsScene;
    QPixmap fondoImg(":/fondos/fondo_nivel1.png");
    QGraphicsPixmapItem *fondo = new QGraphicsPixmapItem(fondoImg);
    fondo->setPos(0, -11520);
    nivelScene->addItem(fondo);

   //
    jugador = new goku_1();
    jugador->setPos(512, 500);
    nivelScene->addItem(jugador);

    vista = new QGraphicsView;
    vista->setScene(nivelScene);
    vista->setFixedSize(1024, 768);
    vista->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    vista->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    nivelScene->setSceneRect(0, -11520, 1024, 12288);

    QRect screenGeometry = QApplication::primaryScreen()->geometry();
    int x = (screenGeometry.width() - vista->width()) / 2;
    int y = (screenGeometry.height() - vista->height()) / 2;
    vista->move(x, y);

    QObject::connect(jugador, &goku_1::meMuevo, [=](QGraphicsItem *yo) {
        QPointF centro = yo->pos();
        if (centro.y() > -11400 && centro.y() < 780) {
            vista->centerOn(yo);
        }
    });

    vista->show();

    premio *p = new premio;
    p->setPos(375, -11000);
    nivelScene->addItem(p);

    timerSpawn = new QTimer(this);
    connect(timerSpawn, &QTimer::timeout, this, [=]() { spawn(); });
    timerSpawn->start(2000);

    timerColision = new QTimer(this);
    connect(timerColision, &QTimer::timeout, this, [=]() { verificarColisiones(); });
    timerColision->start(50);
}
void nivel_1::spawn() {
    int tipo = rand() % 3;
    enemigos *nuevo = nullptr;

    switch (tipo) {
    case 0: {
        enemigo_verde *e = new enemigo_verde(jugador);
        e->setPos(rand() % 924 + 50, -11500);
        nuevo = e;
        break;
    }
    case 1: {
        enemigo_rojo *e = new enemigo_rojo;
        e->setPos(rand() % 924 + 50, -11500);
        nuevo = e;
        break;
    }
    case 2: {
        enemigo_azul *e = new enemigo_azul;
        e->setPos(rand() % 924 + 50, -11500);
        nuevo = e;
        break;
    }
    }

    if (nuevo)
        nivelScene->addItem(nuevo);
}

void nivel_1::verificarColisiones() {
    if (!jugador) return;

    QList<QGraphicsItem *> colisiones = jugador->collidingItems();
    for (QGraphicsItem *item : colisiones) {
        /*
        if (typeid(*item) == typeid(enemigo_rojo) || typeid(*item) == typeid(enemigo_azul)) {
            timerSpawn->stop();
            timerColision->stop();
            jugador->setEnabled(false);
            mostrarGameOver();
            return;
        }

        if (typeid(*item) == typeid(enemigo_verde)) {
            jugador->setEnabled(false);
            QTimer::singleShot(3000, jugador, [=]() {
                jugador->setEnabled(true);
            });

            nivelScene->removeItem(item);
            delete item;
            return;
        }
            */
        // 🚀 Transición a nivel 2 al colisionar con un premio
        if (typeid(*item) == typeid(premio)) {
            // ⚠️ Pausar temporizadores
            if (timerSpawn) timerSpawn->stop();
            if (timerColision) timerColision->stop();

            // ⚠️ Ocultar vista de nivel_1 (pero no eliminarla)
            if (vista) vista->hide();

            // ⚠️ Mostrar transición (no elimina nada aún)
            paso_de_nivel *transicion = new paso_de_nivel();
            transicion->show();

            return;
        }
    }
}

void nivel_1::mostrarGameOver() {
    timerSpawn->stop();
    timerColision->stop();
    jugador->setEnabled(false);

    QPointF centroVista = vista->mapToScene(vista->viewport()->rect().center());

    QGraphicsRectItem *overlay = new QGraphicsRectItem();
    overlay->setRect(vista->mapToScene(vista->viewport()->rect()).boundingRect());
    overlay->setBrush(QBrush(QColor(0, 0, 0, 150)));
    overlay->setZValue(9);
    nivelScene->addItem(overlay);

    QGraphicsPixmapItem *gameOver = new QGraphicsPixmapItem(QPixmap(":/fondos/perdio.png"));
    gameOver->setZValue(10);
    gameOver->setPos(centroVista.x() - gameOver->boundingRect().width() / 2,
                     centroVista.y() - gameOver->boundingRect().height() / 2);
    nivelScene->addItem(gameOver);

    QTimer::singleShot(5000, this, [=]() {
        QWidget *ventana = new QWidget;
        ventana->setWindowTitle("Game Over");

        QPushButton *reintentar = new QPushButton("Reintentar");
        QPushButton *menu = new QPushButton("Volver al menú");

        QVBoxLayout *layout = new QVBoxLayout;
        layout->addWidget(reintentar);
        layout->addWidget(menu);
        ventana->setLayout(layout);

        connect(reintentar, &QPushButton::clicked, [=]() {
            ventana->close();
            reiniciarNivel();
        });

        connect(menu, &QPushButton::clicked, [=]() {
            ventana->close();
            vista->close();
            MainWindow *menuPrincipal = new MainWindow;
            menuPrincipal->show();
        });

        ventana->setFixedSize(200, 150);
        ventana->show();
    });
}

void nivel_1::reiniciarNivel() {
    if (timerSpawn) {
        timerSpawn->stop();
        delete timerSpawn;
        timerSpawn = nullptr;
    }

    if (timerColision) {
        timerColision->stop();
        delete timerColision;
        timerColision = nullptr;
    }

    if (jugador) {
        nivelScene->removeItem(jugador);
        delete jugador;
        jugador = nullptr;
    }

    QList<QGraphicsItem *> items = nivelScene->items();
    for (QGraphicsItem *item : items) {
        nivelScene->removeItem(item);
        delete item;
    }

    if (vista) {
        vista->close();
        delete vista;
        vista = nullptr;
    }

    if (nivelScene) {
        delete nivelScene;
        nivelScene = nullptr;
    }

    ver(); // volver a cargar
}



