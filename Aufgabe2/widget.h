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
#include "iterator.h"


class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr, ElasticNet *net = nullptr);

    void paintEvent(QPaintEvent *event);

private slots:

   void triggerApply();
   void triggerClear();
   void triggerSolve();

private:

    ElasticNet *net;
    Iterator *iterator;

    QTimer *timerApply;
    QPushButton *clearNet, *solveNet, *start, *stop;
    QSpinBox *itermax;
    QDoubleSpinBox *a, *b, *K, *cvratio, *r;
    QLabel *text_a, *text_b, *text_K, *text_itermax,*text_cvratio, *text_r;

};

#endif // WIDGET_H
