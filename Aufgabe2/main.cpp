#include "widget.h"
#include <QApplication>
#include "elasticnet.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    ElasticNet net;
    net.addCity(0.75,0.8);
    net.addCity(0.5,0.2);
    net.addCity(0.2,0.9);
    net.addCity(0.4,0.99);
    net.addCity(0.1,0.1);
    net.addCity(0.3,0.2);
    net.addCity(0.1,0.5);

    QApplication a(argc, argv);

    Widget w(nullptr, &net);
    w.setFixedSize(500,500);
    w.show();

    return a.exec();
}
