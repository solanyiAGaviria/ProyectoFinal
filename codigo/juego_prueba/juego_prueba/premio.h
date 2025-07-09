#ifndef PREMIO_H
#define PREMIO_H

#include <QObject>
#include <QGraphicsPixmapItem>

class premio : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    premio();
};

#endif // PREMIO_H
