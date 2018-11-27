#include "Iterator.h"
#include "ElasticNet.h"
#include "Point.h"
#include "math.h"
#include <iostream> //testing

using namespace std;

Iterator::Iterator()
: iterMax(10000), iterCounter(0), etaTarget(5*pow(10, -3)), initialTemperature(0.1),
  alpha(1.0), beta(1.0), net()
{
    this->currentTemperature = this->initialTemperature;
}

Iterator::Iterator(ElasticNet *net)
: iterMax(10000), iterCounter(0), etaTarget(5*pow(10, -3)), initialTemperature(0.1), alpha(1.0), beta(1.0), net(net)
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

     int numberNodes = this->net->getNumberNodes();

     Point * deltaY = new Point[numberNodes];

     vector<Point> nodes = this->net->getNodes();
     vector<Point> cities = this->net->getCities();


      //used to calc vIA
     Point deltaYa = Point();

     int a_counter = 0;

     for(auto a = nodes.begin(); a != nodes.end(); a++){
        double vIA = 0;
         for(auto i = cities.begin(); i != cities.end(); i++){
            double denominator = 0;
             for(auto b = nodes.begin(); b != nodes.end(); b++){
                 //iterate through nodes again to calc denominator of vIA
                 denominator += exp(-(pow((*i-*b).magnitude(),2))/getT());
             }
             vIA = exp(-(pow((*i - *a).magnitude(),2))/getT())/denominator;

             deltaYa += (*i - *a) * vIA;

         }

         deltaYa *= getAlpha();

         auto left = a-1;
         auto right = a+1;

         if (left < nodes.begin())
             left += numberNodes;

         if (right >= nodes.end())
             right -= numberNodes;

         deltaYa += (*left + *right - (*a * 2)) * getBeta()*getCurrentTemperature();
                                     //c++ doesnt support modulo op. with negative values

         deltaY[a_counter] = deltaYa;


         //reset
         deltaYa = Point();

         a_counter++;

     }

     a_counter = 0;

         for(int a = 0; a < net->getNumberNodes(); a++){
             net->changeNet(a, deltaY[a]);
        }


 iterCounter += 1;

}

 double Iterator::calc_eta(){

    double dist = 0;
    double distMin = 100000;
    double distMax = -100000;

    vector<Point> nodes = this->net->getNodes();
    vector<Point> cities = this->net->getCities();

    for(auto i = cities.begin(); i != cities.end(); i++){
        for(auto a = nodes.begin(); a != nodes.end(); a++){
            dist = (*i - *a).magnitude();
            distMin = min(dist, distMin);
        }
        distMax = max(distMin, distMax);
    }

    return distMax;

 }

void Iterator::solve(){

//	for(auto iterator=0; iterator < this->iterMax; iterator++){

//		// Implement if-statement to check precision etaTarget here
//		this->apply();
//	}
    while((calc_eta() > etaTarget)||(iterCounter < iterMax)){
        apply();
    }

}

// void Iterator::test(){
// 	this->net->setRadius(2.0);
// }
