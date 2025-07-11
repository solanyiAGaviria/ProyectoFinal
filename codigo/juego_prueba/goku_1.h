#ifndef GOKU_1_H
#define GOKU_1_H

#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QObject>
#include <QPixmap>
#include <QVector>

class goku_1 : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

public:
    goku_1();

    void keyPressEvent(QKeyEvent *event) override;

signals:
    void meMuevo(QGraphicsItem *yo);

private:
    QPixmap spriteSheet;
    QRect recortes[3];  // 3 cuadros para caminar
    int frame;
    bool direccion_izquierda;
};

#endif // GOKU_1_H
