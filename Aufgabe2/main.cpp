#include "widget.h"
#include <QApplication>
#include "elasticnet.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    // Initialize a net and an application
    ElasticNet net;
    QApplication a(argc, argv);

    // Create the widget with a pointer to the given net
    Widget w(nullptr, &net);
    w.setFixedSize(500,500);
    w.show();

    return a.exec();
}
