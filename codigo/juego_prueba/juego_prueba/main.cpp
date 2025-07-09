#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow w;
    w.show();  // 👈 Esto asegura que la ventana principal se muestre al inicio

    return app.exec();
}
