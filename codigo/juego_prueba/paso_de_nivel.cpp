#include "paso_de_nivel.h"

paso_de_nivel::paso_de_nivel(QWidget *parent) : QWidget(parent) {
    setStyleSheet("background-color: black;");
    setFixedSize(1024, 768);

    mensaje = new QLabel("Continuemos con el entrenamiento", this);
    mensaje->setStyleSheet("color: white; font-size: 28px;");
    mensaje->setAlignment(Qt::AlignCenter);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(mensaje);
    setLayout(layout);

    QTimer::singleShot(5000, this, SLOT(iniciarNivel2()));
}

void paso_de_nivel::iniciarNivel2() {
    this->close();  // Cierra pantalla de transición

    nivel_2 *nivel = new nivel_2();  // Inicia nivel 2
    nivel->ver();

    emit nivel2Iniciado();  // Puedes conectar esto si necesitas eliminar nivel_1 después
}

