#ifndef PASO_DE_NIVEL_H
#define PASO_DE_NIVEL_H

#include <QWidget>
#include <QTimer>
#include <QLabel>
#include <QVBoxLayout>
#include "nivel_2.h"

class paso_de_nivel : public QWidget {
    Q_OBJECT

public:
    paso_de_nivel(QWidget *parent = nullptr);

private slots:
    void iniciarNivel2();

private:
    QLabel *mensaje;

signals:
    void nivel2Iniciado();

};

#endif // PASO_DE_NIVEL_H
