#include "mainwindow.h"
#include "nivel_1.h"

#include <QVBoxLayout>
#include <QWidget>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Crear contenedor central
    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    // Crear fondo
    fondo = new QLabel(central);
    fondo->setPixmap(QPixmap("C:/Users/Solanyi/Documents/GitHub/ProyectoFinal/codigo/juego_prueba/juego_prueba/entrada.png"));
    fondo->setScaledContents(true);
    fondo->resize(1202, 723); // Tamaño de la imagen

    // Crear botón
    botonIniciar = new QPushButton("Iniciar Juego", central);
    botonIniciar->setFixedSize(200, 50);
    botonIniciar->setStyleSheet("font-size: 18px; background-color: orange;");

    // Crear layout para centrar el botón sobre el fondo
    QVBoxLayout *layout = new QVBoxLayout(central);
    layout->addStretch();
    layout->addWidget(botonIniciar, 0, Qt::AlignCenter);
    layout->addStretch();

    // El fondo debe estar detrás del layout
    fondo->lower();

    // Conectar botón
    connect(botonIniciar, &QPushButton::clicked, this, &MainWindow::iniciarJuego);

    setFixedSize(1202, 723);
    setWindowTitle("Pantalla Principal");
}

MainWindow::~MainWindow()
{
}

void MainWindow::iniciarJuego()
{
    nivel_1 *juego = new nivel_1;
    juego->ver();
    this->close();
}
