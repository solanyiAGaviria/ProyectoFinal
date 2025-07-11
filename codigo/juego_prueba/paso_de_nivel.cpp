#include "paso_de_nivel.h"
#include "nivel_2.h"

#include <QApplication>
#include <QScreen>

paso_de_nivel::paso_de_nivel(QWidget *parent) : QWidget(parent) {
    // Tamaño y estilo
    setFixedSize(600, 600);
    setStyleSheet("background-color: black;");

    mensaje = new QLabel("¡Continuemos con el entrenamiento!", this);
    mensaje->setAlignment(Qt::AlignCenter);
    mensaje->setStyleSheet("color: orange; font-size: 32px; font-family: 'Comic Sans MS';");

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(mensaje);
    setLayout(layout);

    // Centrar la ventana en pantalla
    QRect screenGeometry = QGuiApplication::primaryScreen()->geometry();
    move(screenGeometry.center() - rect().center());

    // Espera 5 segundos antes de cambiar al nivel 2
    QTimer::singleShot(5000, this, SLOT(cambiarANivel2()));
}

void paso_de_nivel::cambiarANivel2() {
    // Crear nivel 2
    nivel_2 *nivel = new nivel_2();
    nivel->ver();

    // Cerrar y eliminar esta ventana
    this->disconnect();
    this->close();
    this->deleteLater();
}
