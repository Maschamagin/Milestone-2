#include <QRectF>
#include <QPainter>
#include <vector>
#include "widget.h"
#include "point.h"
#include <QDebug>

using namespace std;


Widget::Widget(QWidget *parent, ElasticNet *net) :
    QWidget(parent), net(net)
{
    //initialize buttons

    addCity = new QPushButton("Add City",this);
    addCity->setGeometry(10,10,100,30);

    showNet = new QPushButton("Show Net",this);
    showNet->setGeometry(10,40,100,30);

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




    //initialize spinbox

    a = new QSpinBox(this);
    b = new QSpinBox(this);
    K = new QDoubleSpinBox(this);
    cvratio = new QDoubleSpinBox(this);
    r = new QDoubleSpinBox(this);

    itermax = new QSpinBox(this);

    //set property of spinbox

    //set geometry

    a->setGeometry(10,100,80,20);
    b->setGeometry(10,145,80,20);
    K->setGeometry(10,190,80,20);
    itermax->setGeometry(10,235,80,20);
    cvratio->setGeometry(10,280,80,20);
    r->setGeometry(10,325,80,20);

    //defult values

    a->setValue(1);
    b->setValue(1);
    K->setValue(0.1);
    itermax->setValue(10000);
    cvratio->setValue(2.5);
    r->setValue(0.1);

    //set interval and steps of spinbox respectively doublespinbox

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







    //connect statements

    connect(showNet,SIGNAL(clicked()),this,SLOT(triggerShow()));

    connect(a,SIGNAL(valueChanged(int)),this,SLOT(getAlpha(int)));
    connect(b,SIGNAL(valueChanged(int)),this,SLOT(getBeta(int)));
    connect(K,SIGNAL(valueChanged(int)),this,SLOT(getCurrentTemperature(int)));
    connect(itermax,SIGNAL(valueChanged(int)),this,SLOT(getIterMax(int)));
    connect(cvratio,SIGNAL(valueChanged(int)),this,SLOT(getCVRatio(int)));
    connect(r,SIGNAL(valueChanged(int)),this,SLOT(getRadius(int)));
}

void Widget::paintEvent(QPaintEvent *event){

    QPainter painter(this);

    if(net){
        vector<Point> nodes = net->getNodes();
        for(auto i = nodes.begin();i != nodes.end(); ++i){
            QRectF node(100+(200*i->x),100+(200*i->y),10,10);
            qDebug() << i->x << "," << i->y << endl;
            painter.drawRect(node);

         }
    }

    painter.end();

}

void Widget::triggerShow(){
    repaint();
}
