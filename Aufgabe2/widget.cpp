#include <QRectF>
#include <QPainter>
#include <vector>
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
    iterator = new Iterator(net);

    QPalette blackText;
    blackText.setColor(QPalette::Text,Qt::black);

    timerApply = new QTimer(this);

    clearNet = new QPushButton("Clear Net",this);
    clearNet->setGeometry(10,10,120,30);

    solveNet = new QPushButton("Solve Net",this);
    solveNet->setGeometry(10,40,120,30);

    start = new QPushButton("Start Iterator",this);
    start->setGeometry(130,10,120,30);
    stop = new QPushButton("Stop Iterator", this);
    stop->setGeometry(130,40,120,30);

    //initialize textlabels

    text_a = new QLabel(this);
    text_b = new QLabel(this);
    text_K = new QLabel(this);
    text_itermax = new QLabel(this);
    text_cvratio = new QLabel(this);
    text_r = new QLabel(this);

    //set geometry of textlabel

    text_a->setGeometry(10,80,80,15);
    text_b->setGeometry(10,125,80,15);
    text_K->setGeometry(10,170,80,15);
    text_itermax->setGeometry(10,215,80,15);
    text_cvratio->setGeometry(10,260,80,15);
    text_r->setGeometry(10,305,80,15);

    //set Text of Labels

    text_a->setText("Alpha");
    text_b->setText("Beta");
    text_K->setText("Temperature");
    text_itermax->setText("Itermax");
    text_cvratio->setText("CVRatio");
    text_r->setText("Radius");


    //Initialize spinboxes

    a = new QDoubleSpinBox(this);
    b = new QDoubleSpinBox(this);
    K = new QDoubleSpinBox(this);
    cvratio = new QDoubleSpinBox(this);
    r = new QDoubleSpinBox(this);

    itermax = new QSpinBox(this);

    //Set properties of Spinboxex

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

    a->setValue(1);
    b->setValue(1);
    K->setValue(0.1);
    itermax->setValue(10000);
    cvratio->setValue(2.5);
    r->setValue(0.1);

    // Connect all spinboxes to respective iterator slots

    connect(a,SIGNAL(valueChanged(double)),iterator,SLOT(setAlpha(double)));
    connect(b,SIGNAL(valueChanged(double)),iterator,SLOT(setBeta(double)));
    connect(K,SIGNAL(valueChanged(double)),iterator,SLOT(setInitialTemperature(double)));
    connect(itermax,SIGNAL(valueChanged(int)),iterator,SLOT(setIterMax(int)));
    connect(cvratio,SIGNAL(valueChanged(double)),net,SLOT(setCVRatio(double)));
    connect(r,SIGNAL(valueChanged(double)),net,SLOT(setRadius(double)));

    // Connect timer to apply function
    timerApply->setInterval(50);
    connect(timerApply,SIGNAL(timeout()),this,SLOT(triggerApply()));

    // Connect buttons
    connect(clearNet,SIGNAL(clicked()),this,SLOT(triggerClear()));
    connect(solveNet,SIGNAL(clicked()),this,SLOT(triggerSolve()));
    connect(start,SIGNAL(clicked()),timerApply,SLOT(start()));
    connect(stop,SIGNAL(clicked()),timerApply,SLOT(stop()));
}

void Widget::paintEvent(QPaintEvent *event){

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
            QRectF city(STARTX+(SCALE*i->x),STARTY+(SCALE*i->y),10,10);
            // qDebug() << "City: " << i->x << "," << i->y << endl;
            painter.drawRect(city);
        }
    }

    painter.end();
}

void Widget::triggerApply(){
    if(iterator->calcEta() > iterator->getEtaTarget()){
        iterator->apply();
    }
    repaint();
}

void Widget::triggerClear(){
    net->clearNet();
    repaint();
}

void Widget::triggerSolve(){
    iterator->solve();
    repaint();
}
