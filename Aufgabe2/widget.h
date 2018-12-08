#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QPaintEvent>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QSlider>
#include "elasticnet.h"
#include "point.h"
#include "iterator.h"


class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr, ElasticNet *net = nullptr);

    // Triggers the painting of the map including the current status of the net
    void paintEvent(QPaintEvent *event);
    // Checks if mouse was clicked on the map and adds a city on that position
    void mousePressEvent(QMouseEvent *event);

private slots:

    // Called by Timer, applies iterator once and repaints
    void triggerApply();
    // Called by "ClearNet"-Button and clears the net
    void triggerClear();
    // Called b "SolveNet"-Button and solves the net at once (no visualization of steps)
    void triggerSolve();
    // Called by a changed Value in the Slider, adjustes the speed of the "apply"-Timer
    void changeSpeed(int speed);

private:

    // Net and iterator as attributes of the widget
    ElasticNet *net;
    Iterator *iterator;

    // Interface elements
    QTimer *timerApply;
    QPushButton *clearNet, *solveNet, *start, *stop;
    QSpinBox *itermax;
    QSlider *iteratorSlider;
    QDoubleSpinBox *a, *b, *K, *cvratio, *r, *etaTarget;
    QLabel *text_a, *text_b, *text_K, *text_itermax,*text_cvratio, *text_r, *text_etaTarget;

};

#endif // WIDGET_H
