#include "iterator.h"
#include "elasticNet.h"
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

    setCurrentTemperature();

    int numberNodes = net->getNumberNodes();

    //set up array to save all deltaY values
    Point * deltaY = new Point[numberNodes];

    double vIA = 0;
    double denominator = 0; //used to calc vIA
    Point deltaYa = Point();


    for(int a = 0; a < numberNodes; a++){
        //iterate through all elastic net nodes

        for(int i = 0; i < net->getNumberCities(); i++){
            //iterate through cities
            for(int b = 0; b < numberNodes; b++){
                //iterate through nodes again to calc denominator of vIA
                denominator += exp(-(pow((net->getCities()[i] - net->getNodes()[b]).magnitude(),2))/getT());
            }
            vIA = exp(-(pow((net->getCities()[i] - net->getNodes()[a]).magnitude(),2))/getT())/denominator;

            deltaYa += (net->getCities()[i] - net->getNodes()[a]) * vIA;

        }

        deltaYa *= getAlpha();

        deltaYa += (net->getNodes()[((a-1)%numberNodes + numberNodes)%numberNodes] + net->getNodes()[a] - (net->getNodes()[(a+1)%numberNodes] * 2)) * getBeta()*getCurrentTemperature();
                                    //c++ doesnt support modulo op. with negative values

        deltaY[a] = deltaYa;


        //reset
        denominator = 0;
        deltaYa = Point();


    }

    //at this point all deltaYa are calculated and saved in deltaY
    //in the next loop all yA get changed by deltaYa

    for(int a = 0; a < net->getNumberNodes(); a++){
        //net->getNodes()[a] += deltaY[a]; ging nicht
        net->changeNet(a, deltaY[a]);
        cout << net->getNodes()[a].x << " " << net->getNodes()[a].y << endl ;
    }


}

// void Iterator::apply(){

//     this->setCurrentTemperature();
//     double K = this->getCurrentTemperature();
//     double T = this->getT();

//     int numberNodes = this->net->getNumberNodes();

//     Point * deltaY = new Point[numberNodes];

//     vector<Point> y = this->net->getNodes();
//     vector<Point> x = this->net->getCities();

//     int a_counter = 0;

//     for(auto a = y.begin(); a != y.end(); ++a){

//         auto aMinusOne = a-1;
//         auto aPlusOne = a+1;

//         if (aMinusOne < y.begin())
//             aMinusOne += numberNodes;

//         if (aPlusOne+1 >= y.end())
//             aPlusOne -= numberNodes;



//         a_counter = 0;

//     }
// }




void Iterator::solve(){

    for(iterCounter = 0; iterCounter < this->iterMax; ++iterCounter){

        // Implement if-statement to check precision etaTarget here
        this->apply();
    }
}

// void Iterator::test(){
// 	this->net->setRadius(2.0);
// }
