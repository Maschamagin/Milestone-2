#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QPaintEvent>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QLabel>
#include "elasticnet.h"
#include "point.h"


class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr, ElasticNet *net = nullptr);

    void paintEvent(QPaintEvent *event);

private slots:

   void triggerShow();

private:

    QTimer *timer;
    QPushButton *clearNet;
    ElasticNet *net;
    QSpinBox *a, *b, *itermax;
    QDoubleSpinBox *K, *cvratio, *r;
    QLabel *text_a, *text_b, *text_K, *text_itermax,*text_cvratio, *text_r;

};

#endif // WIDGET_H
