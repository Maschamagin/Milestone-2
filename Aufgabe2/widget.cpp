#include <QRectF>
#include <QPainter>
#include <vector>
#include <cmath>
#include "widget.h"
#include "point.h"
#include <QDebug>
#include <QTimer>

#define STARTX 150
#define STARTY 100
#define SCALE 300

using namespace std;

Widget::Widget(QWidget *parent, ElasticNet *net) :
    QWidget(parent), net(net)
{
    // Initialize a new iterator and set Eta Target to default
    iterator = new Iterator(net);

    // Define Palette to display black text
    QPalette blackText;
    blackText.setColor(QPalette::Text,Qt::black);

    // Define timer and interface elements
    timerApply = new QTimer(this);

    clearNet = new QPushButton("Clear Net",this);
    clearNet->setGeometry(10,10,120,30);

    solveNet = new QPushButton("Solve Net",this);
    solveNet->setGeometry(10,40,120,30);

    start = new QPushButton("Start Iterator",this);
    start->setGeometry(130,10,120,30);
    stop = new QPushButton("Stop Iterator", this);
    stop->setGeometry(130,40,120,30);

    iteratorSlider = new QSlider(Qt::Horizontal,this);
    iteratorSlider->setGeometry(260,25,200,30);
    iteratorSlider->setMaximum(10);
    iteratorSlider->setMinimum(1);
    iteratorSlider->setValue(1);

    text_a = new QLabel(this);
    text_b = new QLabel(this);
    text_K = new QLabel(this);
    text_itermax = new QLabel(this);
    text_cvratio = new QLabel(this);
    text_r = new QLabel(this);
    text_etaTarget = new QLabel(this);

    text_a->setGeometry(10,80,80,15);
    text_b->setGeometry(10,125,80,15);
    text_K->setGeometry(10,170,80,15);
    text_itermax->setGeometry(10,215,80,15);
    text_cvratio->setGeometry(10,260,80,15);
    text_r->setGeometry(10,305,80,15);
    text_etaTarget->setGeometry(10,350,100,15);

    text_a->setText("Alpha");
    text_b->setText("Beta");
    text_K->setText("Temperature");
    text_itermax->setText("Itermax");
    text_cvratio->setText("CVRatio");
    text_r->setText("Radius");
    text_etaTarget->setText("Accuracy (*10^-3)");

    a = new QDoubleSpinBox(this);
    b = new QDoubleSpinBox(this);
    K = new QDoubleSpinBox(this);
    cvratio = new QDoubleSpinBox(this);
    r = new QDoubleSpinBox(this);
    etaTarget = new QSpinBox(this);

    itermax = new QSpinBox(this);

    a->setPalette(blackText);
    a->setGeometry(10,100,80,20);
    b->setPalette(blackText);
    b->setGeometry(10,145,80,20);
    K->setPalette(blackText);
    K->setGeometry(10,190,80,20);
    itermax->setPalette(blackText);
    itermax->setGeometry(10,235,80,20);
    cvratio->setPalette(blackText);
    cvratio->setGeometry(10,280,80,20);
    r->setPalette(blackText);
    r->setGeometry(10,325,80,20);
    etaTarget->setPalette(blackText);
    etaTarget->setGeometry(10,370,80,20);



    a->setMinimum(0);
    a->setMaximum(1000);
    a->setSingleStep(1);

    b->setMinimum(0);
    b->setMaximum(1000);
    b->setSingleStep(1);

    K->setMinimum(0);
    K->setMaximum(100);
    K->setSingleStep(0.1);

    itermax->setMinimum(0);
    itermax->setMaximum(1000000);
    itermax->setSingleStep(1);

    cvratio->setMinimum(0);
    cvratio->setMaximum(50);
    cvratio->setSingleStep(0.5);

    r->setMinimum(0);
    r->setMaximum(10);
    r->setSingleStep(0.1);

    etaTarget->setMinimum(0);
    etaTarget->setMaximum(1000);
    etaTarget->setSingleStep(1);


    a->setValue(1);
    b->setValue(1);
    K->setValue(0.1);
    itermax->setValue(10000);
    cvratio->setValue(2.5);
    r->setValue(0.1);
    etaTarget->setValue(5);

    // Connect all SpinBoxes to respective properties of net and iterator

    connect(a,SIGNAL(valueChanged(double)),iterator,SLOT(setAlpha(double)));
    connect(b,SIGNAL(valueChanged(double)),iterator,SLOT(setBeta(double)));
    connect(K,SIGNAL(valueChanged(double)),iterator,SLOT(setInitialTemperature(double)));
    connect(itermax,SIGNAL(valueChanged(int)),iterator,SLOT(setIterMax(int)));
    connect(cvratio,SIGNAL(valueChanged(double)),net,SLOT(setCVRatio(double)));
    connect(r,SIGNAL(valueChanged(double)),net,SLOT(setRadius(double)));
    connect(etaTarget,SIGNAL(valueChanged(double)),iterator, SLOT(setEtaTarget()));

    // Connect timer to apply function
    timerApply->setInterval(100);
    connect(timerApply,SIGNAL(timeout()),this,SLOT(triggerApply()));

    // Connect buttons to iterator and net slots
    connect(clearNet,SIGNAL(clicked()),this,SLOT(triggerClear()));
    connect(solveNet,SIGNAL(clicked()),this,SLOT(triggerSolve()));
    connect(start,SIGNAL(clicked()),timerApply,SLOT(start()));
    connect(stop,SIGNAL(clicked()),timerApply,SLOT(stop()));
    connect(iteratorSlider,SIGNAL(valueChanged(int)),this,SLOT(changeSpeed(int)));
}

void Widget::paintEvent(QPaintEvent *event){

    // Initialize painter and draw map borders
    QPainter painter(this);
    painter.setPen(QPen(Qt::white,2));
    painter.drawRect(QRectF(STARTX,STARTY,SCALE+10,SCALE+10));

    if(net){
        // Draw all nodes and connecting lines
        vector<Point> nodes = net->getNodes();
        for(auto i = nodes.begin();i != nodes.end(); ++i){

            // Set color to red for nodes
            painter.setBrush(QBrush(Qt::red));
            painter.setPen(Qt::red);

            // Draw ellipse for each node
            QRectF node(STARTX+(SCALE*i->x),STARTY+(SCALE*i->y),5,5);
            // qDebug() << "Node: " << i->x << "," << i->y << endl;
            painter.drawEllipse(node);

            // Draw lines to neighbour node
            auto nextI = i+1;
            if (nextI >= nodes.end())
                        nextI -= net->getNumberNodes();

            QRectF nextNode(STARTX+(SCALE*nextI->x),STARTY+(SCALE*nextI->y),5,5);
            painter.drawLine(STARTX+2.5+(SCALE*i->x),STARTY+2.5+(SCALE*i->y),
                             STARTX+2.5+(SCALE*nextI->x),STARTY+2.5+(SCALE*nextI->y));
         }

        // Draw all cities
        vector<Point> cities = net->getCities();
        for(auto i = cities.begin();i != cities.end(); ++i){
            painter.setPen(Qt::white);
            painter.setBrush(QBrush(Qt::black));

            QRectF city(STARTX-5+(SCALE*i->x),STARTY-5+(SCALE*i->y),10,10);
            // qDebug() << "City: " << i->x << "," << i->y << endl;
            painter.drawRect(city);
        }
    }

    painter.end();
}

void Widget::mousePressEvent(QMouseEvent *event){

    // Read x- and y-mouse position
    double xpos = event->x();
    double ypos = event->y();

    // Check if mouse is in range of map
    if(xpos > STARTX && xpos < STARTX+SCALE
       && ypos > STARTY && ypos < STARTY+SCALE){

        // Calculate the real net position
        double netX = (xpos-(STARTX+SCALE))/SCALE + 1;
        double netY = (ypos-(STARTY+SCALE))/SCALE + 1;

        // Check if a city is in range of 2*EtaTarget
        vector<Point> cities = net->getCities();
        bool cityNearby = false;

        for(auto i = cities.begin(); i != cities.end();i++){
            double minDist = 2 * iterator->getEtaTarget();

            if(abs(netX-(i->x)) < minDist && abs(netY-(i->y)) < minDist)
                cityNearby = true;
        }

        // If city placement is valid, add the city to the net
        if(!cityNearby){
            net->addCity(netX,netY);
        }
    }

    // Repaint as net has changed
    repaint();
}

void Widget::triggerApply(){
    // Apply the algorithm until given precision target is reached
    if(iterator->calcEta() > iterator->getEtaTarget()){
        iterator->apply();
    }
    // Repaint as net has changed
    repaint();
}

void Widget::triggerClear(){
    // Clear the net
    net->clearNet();

    // Reset the iterator
    iterator->setIterCounter(0);

    // Repaint as net has changed
    repaint();
}

void Widget::triggerSolve(){
    // Solve the whole problem at once and visualize afterwards
    // Fast and exact way of solving, much faster than with visualization
    iterator->solve();
    // Repaint as net has changed
    repaint();
}

void Widget::changeSpeed(int speed){
    // Change speed of Timer
    timerApply->setInterval(100/speed);
}
