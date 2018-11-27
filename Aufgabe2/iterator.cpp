#include "iterator.h"
#include "elasticnet.h"
#include "point.h"
#include "math.h"
#include <iostream> //testing

using namespace std;

Iterator::Iterator()
: iterMax(10000), iterCounter(0), etaTarget(0), initialTemperature(0.1),
  alpha(1.0), beta(1.0), net()
{
    this->currentTemperature = this->initialTemperature;
}

Iterator::Iterator(ElasticNet *net)
: iterMax(10000), iterCounter(0), etaTarget(0), initialTemperature(0.1), alpha(1.0), beta(1.0), net(net)
{
    this->currentTemperature = this->initialTemperature;
}

Iterator::Iterator(ElasticNet *net, double alpha, double beta, double temperature)
: iterMax(10000), etaTarget(0), initialTemperature(temperature), alpha(alpha), beta(beta), net(net)
{
    this->currentTemperature = this->initialTemperature;
}

void Iterator::setInitialTemperature(double temp){
    this->initialTemperature = temp;
 }

void Iterator::setCurrentTemperature(){
    this->currentTemperature = max(pow(0.99,floor(iterCounter/50))*getInitialTemperature(), 0.01);
 }

void Iterator::setIterMax(int iterMax){
    this->iterMax = iterMax;
 }

void Iterator::setAlpha(double alpha){
    this->alpha = alpha;
 }

void Iterator::setBeta(double beta){
    this->beta = beta;
 }

void Iterator::setNet(ElasticNet *net){
    this->net = net;
 }

double Iterator::getInitialTemperature(){
    return this->initialTemperature;
 }

double Iterator::getCurrentTemperature(){
    return this->currentTemperature;
}

double Iterator::getT(){
    return 2*pow(getCurrentTemperature(),2);
}

double Iterator::getIterMax(){
    return this->iterMax;
}

double Iterator::getAlpha(){
    return this->alpha;
}

double Iterator::getBeta(){
    return this->beta;
}

ElasticNet* Iterator::getNet(){
    return this->net;
}

void Iterator::apply(){

     this->setCurrentTemperature();
     double K = this->getCurrentTemperature();
     double T = this->getT();

     int numberNodes = this->net->getNumberNodes();

     Point * deltaY = new Point[numberNodes];

     vector<Point> nodes = this->net->getNodes();
     vector<Point> cities = this->net->getCities();

     Point deltaYa = Point();

     int a_counter = 0;

     for(auto a = nodes.begin(); a != nodes.end(); a++){

         double vIA = 0;

         for(auto i = cities.begin(); i != cities.end(); i++){

             double denominator = 0; //used to calc vIA

             for(auto b = nodes.begin(); b != nodes.end(); b++){
                 //iterate through nodes again to calc denominator of vIA
                 //denominator += exp(-(pow((net->getCities()[i] - net->getNodes()[b]).magnitude(),2))/getT());
                 denominator += exp(-(pow((*i-*b).magnitude(),2))/T);
                 //sum(b e nodes) e^((|x_i - y_b|^2)/T)
             }
             vIA = exp(-(pow((*i - *a).magnitude(),2))/T)/denominator;
             //e^((|x_i - y_a|^2)/T) / sum(b e nodes) e^((|x_i - y_b|^2)/T)

             deltaYa += (*i - *a) * vIA;

         }

         deltaYa *= getAlpha();

         auto left = a-1;
         auto right = a+1;

         if (left < nodes.begin())
             left += numberNodes;

         if (right >= nodes.end())
             right -= numberNodes;

         deltaYa += (*left + *right - (*a * 2)) * getBeta()*K;
         deltaY[a_counter] = deltaYa;

         //reset
         deltaYa = Point();
         a_counter++;

     }

     a_counter = 0;

     for(int a = 0; a < net->getNumberNodes(); a++){
             //net->getNodes()[a] += deltaY[a]; ging nicht
             net->changeNet(a, deltaY[a]);
        }


 iterCounter += 1;

 }


void Iterator::solve(){

    for(iterCounter = 0; iterCounter < this->iterMax; ++iterCounter){

        // Implement if-statement to check precision etaTarget here
        this->apply();
    }
}
