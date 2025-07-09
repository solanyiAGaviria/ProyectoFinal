#include "nivel_2.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsTextItem>
#include <QApplication>
#include <QScreen>

nivel_2::nivel_2() {}

void nivel_2::ver() {
    QGraphicsScene *scene = new QGraphicsScene;
    QGraphicsView *view = new QGraphicsView(scene);

    scene->addText("NIVEL 2: ¡Buena suerte!");

    view->setFixedSize(1024, 768);
    view->setSceneRect(0, 0, 1024, 768);
    view->show();

    QRect screenGeometry = QApplication::primaryScreen()->geometry();
    int x = (screenGeometry.width() - view->width()) / 2;
    int y = (screenGeometry.height() - view->height()) / 2;
    view->move(x, y);
}
