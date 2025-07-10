#ifndef BALA_H
#define BALA_H
#include <QGraphicsPixmapItem>
#include<QGraphicsItem>
#include<QObject>
#include <QGraphicsRectItem>

class bala : public QObject ,public QGraphicsRectItem
{
    Q_OBJECT

public:
    bala();
    ~bala();

public slots:
    void mover();
};

#endif // BALA_H
