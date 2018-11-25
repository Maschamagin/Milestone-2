#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include "elasticnet.h"
#include "point.h"
#include <QPaintEvent>


class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr, ElasticNet *net = nullptr);

    void paintEvent(QPaintEvent *event);

private slots:

   void triggerShow();

private:
    QPushButton *addCity, *showNet;
    ElasticNet *net;

};

#endif // WIDGET_H
