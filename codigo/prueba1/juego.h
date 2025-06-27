
// juego.h
#ifndef JUEGO_H
#define JUEGO_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include "goku.h"
#include "fondo.h"

class Juego : public QGraphicsView {
    Q_OBJECT
public:
    Juego(QWidget *parent = nullptr);

private slots:
    void seguirAGoku(int yGoku);

private:
    QGraphicsScene *scene;
    Goku *goku;
};

#endif // JUEGO_H
