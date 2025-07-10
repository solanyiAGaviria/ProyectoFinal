#ifndef PASO_DE_NIVEL_H
#define PASO_DE_NIVEL_H

#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QVBoxLayout>

class paso_de_nivel : public QWidget {
    Q_OBJECT

public:
    explicit paso_de_nivel(QWidget *parent = nullptr);

public slots:
    void cambiarANivel2();

private:
    QLabel* mensaje;
};

#endif // PASO_DE_NIVEL_H
