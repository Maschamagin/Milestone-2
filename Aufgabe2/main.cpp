#include "widget.h"
#include <QApplication>
#include "elasticnet.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    ElasticNet net;
    QApplication a(argc, argv);

    Widget w(nullptr, &net);
    w.setFixedSize(500,500);
    w.show();

    return a.exec();
}
