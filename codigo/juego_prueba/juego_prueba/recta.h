#ifndef RECTA_H
#define RECTA_H
#include<QObject>
#include<QGraphicsRectItem>

class recta : public QObject, public QGraphicsRectItem
{
    Q_OBJECT

public:
    recta();
    void keyPressEvent(QKeyEvent *event) override;
public slots:
    //void spawn();

signals:
    void meMuevo(QGraphicsItem *yo);

};

#endif // RECTA_H
