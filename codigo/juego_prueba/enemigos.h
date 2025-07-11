#ifndef ENEMIGOS_H
#define ENEMIGOS_H

#include <QObject>
#include <QGraphicsPixmapItem> // Cambio aquí

class enemigos : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    explicit enemigos(QObject *parent = nullptr);
    virtual ~enemigos();

public slots:
    virtual void mover();  // Puede ser sobreescrito
};

#endif // ENEMIGOS_H
