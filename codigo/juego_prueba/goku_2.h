#ifndef GOKU_2_H
#define GOKU_2_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QTimer>
#include <QSet>
#include <QPixmap>

class goku_2 : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

public:
    goku_2(int **matriz, int filas, int columnas, int tamano_celda);
    void keyPressEvent(QKeyEvent *evento) override;
    void keyReleaseEvent(QKeyEvent *evento) override;

private slots:
    void saltar();  // Movimiento vertical

private:
    int **matriz_laberinto;
    int filas;
    int columnas;
    int tamano;

    int velocidad_y;
    bool en_el_aire;
    bool puede_saltar;

    QSet<int> teclas_presionadas;
    QTimer* temporizador_salto;

    QPixmap hoja_sprite;
    int ancho_sprite;
    int alto_sprite;
    int animacion_cuadro;
    bool direccion_izquierda;

    bool colision(int nuevaX, int nuevaY);
    bool hayPisoDebajo();
    void actualizarAnimacion(QString accion);
};

#endif // GOKU_2_H
