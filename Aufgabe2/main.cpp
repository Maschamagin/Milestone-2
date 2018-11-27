#include "widget.h"
#include <QApplication>
#include "elasticnet.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    ElasticNet net;
    net.addCity(1.0,1.0);
    net.addCity(0.0,0.0);

    Point ap(1.0,1.0);
    Point bp(2.0,2.0);

    Point cp = ap + bp;

    qDebug() << ap.x << "," << ap.y << endl;
    qDebug() << bp.x << "," << bp.y << endl;
    qDebug() << cp.x << "," << cp.y << endl;

    QApplication a(argc, argv);

    Widget w(nullptr, &net);
    w.setFixedSize(500,500);
    w.show();

    return a.exec();
}
