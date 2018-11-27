#include "widget.h"
#include <QApplication>
#include "elasticnet.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    ElasticNet net;
    net.addCity(1.0,1.0);
    net.addCity(1.0,0.0);
    net.addCity(0.0,1.0);
    net.addCity(0.0,0.0);

    QApplication a(argc, argv);

    Widget w(nullptr, &net);
    w.setFixedSize(500,500);
    w.show();

    return a.exec();
}
