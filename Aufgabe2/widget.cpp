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
    addCity = new QPushButton("Add City",this);
    addCity->setGeometry(10,10,100,30);

    showNet = new QPushButton("Show Net",this);
    showNet->setGeometry(10,40,100,30);

    connect(showNet,SIGNAL(clicked()),this,SLOT(triggerShow()));
}

void Widget::paintEvent(QPaintEvent *event){

    QPainter painter(this);

    if(net){
        vector<Point> nodes = net->getNodes();
        for(auto i = nodes.begin();i != nodes.end(); ++i){
            QRectF node(100+(200*i->x),100+(200*i->y),10,10);
            qDebug() << "Node: " << i->x << "," << i->y << endl;
            painter.drawRect(node);

         }
        vector<Point> cities = net->getCities();
        for(auto i = cities.begin();i != cities.end(); ++i){
            QRectF city(100+(200*i->x),100+(200*i->y),10,10);
            qDebug() << "City: " << i->x << "," << i->y << endl;
            painter.drawRect(city);
        }
    }

    painter.end();

}

void Widget::triggerShow(){
    repaint();
}
