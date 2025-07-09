#ifndef ENEMIGOS_H
#define ENEMIGOS_H

#include <QObject>
#include <QGraphicsRectItem>

class enemigos : public QObject, public QGraphicsRectItem
{
    Q_OBJECT

public:
    explicit enemigos(QObject *parent = nullptr);  // Constructor con parent
    virtual ~enemigos();                           // Destructor virtual

public slots:
    virtual void mover();  // Para que pueda ser sobreescrito
};

#endif // ENEMIGOS_H
